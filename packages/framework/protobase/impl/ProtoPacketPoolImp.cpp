#include "ProtoPacketPoolImp.h"
#include "ProtoPacket.h"
#include "ProtoMutex.h"
#include "ProtoLog.h"
#include "ProtoHelper.h"

ProtoPacketPoolImp::ProtoPacketPoolImp(int limit) : mLimit(limit)
{
	mMutex = new ProtoMutex();
	for( int i=0; i<mLimit; i++ )
	{
		char* buf = new char[MAX_POOL_PACKET_SIZE];
		ProtoPacket* proto = new ProtoPacket(buf, MAX_POOL_PACKET_SIZE);

		mPackets.push_back(proto);
	}
}

ProtoPacketPoolImp::~ProtoPacketPoolImp()
{
	//PLOG("ProtoPacketPoolImp::~ProtoPacketPoolImp.");

	mMutex->lock();
	for( std::deque<IProtoPacket*>::iterator it = mPackets.begin(); it != mPackets.end(); it++ )
	{
		ProtoPacket* packet = (ProtoPacket*)*it;
		if( packet )
		{
			delete packet;
		}
	}
	mPackets.clear();
	mMutex->unlock();

	if( mMutex )
		delete mMutex;
}

//[yunzed]
//back memory copy policy, need optimize.
IProtoPacket*	ProtoPacketPoolImp::newPacket(int uri, const sox::Marshallable& req)
{
	ProtoPacket* packet = NULL;

	std::string content = ProtoHelper::ProtoToString(uri, req);

	mMutex->lock();
	if( mPackets.size() == 0 || content.length() > MAX_POOL_PACKET_SIZE )
	{
		//unlock first:
		mMutex->unlock();

		//alloc from heap:
		int len = content.length();

		if( len >= MAX_PACKET_SIZE )
		{
			PLOG("ProtoPacketPoolImp::newPacket, size too large, uri=", uri);
			return NULL;
		}
		char* buf = new char[len];
		packet = new ProtoPacket(buf, len);
		packet->setConnId(-1);
		packet->setMemType(ProtoPacket::MEM_NEW);
		packet->unmarshal(content.c_str(), content.length());

		return packet;
	}
	packet = (ProtoPacket*)*mPackets.begin();	
	mPackets.pop_front();
	mMutex->unlock();

	packet->setConnId(-1);
	packet->setMemType(ProtoPacket::MEM_POOL);
	packet->marshal(uri, req);

	//PLOG("ProtoPacketPoolImp::newPacket, _id=", packet->_id);

	return packet;
}

IProtoPacket*	ProtoPacketPoolImp::newPacket(const char *data, int len, int connId)
{
	ProtoPacket* packet = NULL;

	if( len >= MAX_PACKET_SIZE )
	{
		PLOG("ProtoPacketPoolImp::newPacket, size too large, len/connId=", len, connId);
		return NULL;
	}

	mMutex->lock();
	if( mPackets.size() == 0 || len > MAX_POOL_PACKET_SIZE )
	{
		//unlock first:
		mMutex->unlock();

		//alloc from heap:
		char* buf = new char[len];
		packet = new ProtoPacket(buf, len);
		packet->setConnId(connId);
		packet->setMemType(ProtoPacket::MEM_NEW);
		packet->unmarshal(data, len);

		//check the packet is valid:
		if( packet->getLength() != len )
		{
			PLOG("ProtoPacketPoolImp::newPacket, size not match, len/getLength()/connId=", len, packet->getLength(), connId);
			//freePacket(packet);
			//don't use freePacket here, because freePacket will use the _len which will be invalid when detect wrong package.
			delete packet;
			packet = NULL;
			PLOG("ProtoPacketPoolImp::newPacket, size not match, return NULL."); 
		}

		return packet;
	}
	packet = (ProtoPacket*)*mPackets.begin();	
	mPackets.pop_front();
	mMutex->unlock();

	packet->setConnId(connId);
	packet->setMemType(ProtoPacket::MEM_POOL);
	packet->unmarshal(data, len);
	//check the packet is valid:
	if( packet->getLength() != len )
	{
		PLOG("ProtoPacketPoolImp::newPacket, size not match, len/getLength()/connId=", len, packet->getLength(), connId);
		//freePacket(packet);
		//don't use freePacket here, because freePacket will use the _len which will be invalid when detect wrong package.
		mMutex->lock();
		mPackets.push_back(packet);
		mMutex->unlock();

		packet = NULL;
		PLOG("ProtoPacketPoolImp::newPacket, size not match, return NULL."); 
	}

	//PLOG("ProtoPacketPoolImp::newPacket, size=", mPackets.size());

	return packet;
}

IProtoPacket*	ProtoPacketPoolImp::newPacket(int uri, const char *data, int len, int connId)
{
	ProtoPacket* proto = NULL;
	int ret = 200;

	if( data == NULL )
		return NULL;
	if( len >= MAX_PACKET_SIZE )
	{
		PLOG("ProtoPacketPoolImp::newPacket, size too large, uri/len/connId=", uri, len, connId);
		return NULL;
	}

	len += 10;	//add up packet header
	char* buf = new char[len];
	memcpy(buf, &len, sizeof(len));
	memcpy(buf+4, &uri, sizeof(uri));
	memcpy(buf+8, &ret, sizeof(short));

	memcpy(buf+10, data, len);

	proto = (ProtoPacket*)newPacket(buf, len, connId);
	//if( proto )
	//{
	//	proto->setConnId(connId);
	//}	

	return proto;	
}

void	ProtoPacketPoolImp::freePacket(IProtoPacket* proto)
{
	ProtoPacket* packet = NULL;
	if( proto == NULL )
		return;

	packet = (ProtoPacket*)proto;
	if( packet->getMemType() == ProtoPacket::MEM_POOL )
	{
		packet->reset();

		mMutex->lock();
		mPackets.push_back(packet);
		mMutex->unlock();

		//PLOG("ProtoPacketPoolImp::freePacket, _id=", packet->_id);
	}
	else
	{
		delete packet;
	}
}

