#include "AudioPacketPoolImp.h"
#include "AudioPacket.h"
#include "ProtoMutex.h"
#include "ProtoLog.h"
#include "ProtoHelper.h"

#define		MAX_POOL_PACKET_SIZE	512
AudioPacketPoolImp::AudioPacketPoolImp(int limit) : mLimit(limit)
{
	mMutex = new ProtoMutex();
	for( int i=0; i<mLimit; i++ )
	{
		char* buf = new char[MAX_POOL_PACKET_SIZE];
		AudioPacket* proto = new AudioPacket(buf, MAX_POOL_PACKET_SIZE);

		mPackets.push_back(proto);
	}
}

AudioPacketPoolImp::~AudioPacketPoolImp()
{
	//PLOG("ProtoPacketPoolImp::~ProtoPacketPoolImp.");

	mMutex->lock();
	for( std::deque<IProtoPacket*>::iterator it = mPackets.begin(); it != mPackets.end(); it++ )
	{
		AudioPacket* packet = (AudioPacket*)*it;
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
IProtoPacket*	AudioPacketPoolImp::newPacket(int uri, const sox::Marshallable& req)
{
	AudioPacket* packet = NULL;

	std::string content = ProtoHelper::AudioProtoToString(uri, req);

	mMutex->lock();
	if( mPackets.size() == 0 || content.length() > MAX_POOL_PACKET_SIZE )
	{
		//unlock first:
		mMutex->unlock();

		//alloc from heap:
		int len = content.length();
		char* buf = new char[len];
		packet = new AudioPacket(buf, len);
		packet->setConnId(-1);
		packet->setMemType(AudioPacket::MEM_NEW);
		packet->unmarshal(content.c_str(), content.length());

		return packet;
	}
	packet = (AudioPacket*)*mPackets.begin();	
	mPackets.pop_front();
	mMutex->unlock();

	packet->setConnId(-1);
	packet->setMemType(AudioPacket::MEM_POOL);
	packet->marshal(uri, req);

	//PLOG("ProtoPacketPoolImp::newPacket, _id=", packet->_id);

	return packet;
}

IProtoPacket*	AudioPacketPoolImp::newPacket(const char *data, int len, int connId)
{
	AudioPacket* packet = NULL;

	mMutex->lock();
	if( mPackets.size() == 0 || len > MAX_POOL_PACKET_SIZE )
	{
		//unlock first:
		mMutex->unlock();

		//alloc from heap:
		char* buf = new char[len];
		packet = new AudioPacket(buf, len);
		packet->setConnId(connId);
		packet->setMemType(AudioPacket::MEM_NEW);
		packet->unmarshal(data, len);

		return packet;
	}
	packet = (AudioPacket*)*mPackets.begin();	
	mPackets.pop_front();
	mMutex->unlock();

	packet->setConnId(connId);
	packet->setMemType(AudioPacket::MEM_POOL);
	packet->unmarshal(data, len);

	//PLOG("ProtoPacketPoolImp::newPacket, size=", mPackets.size());

	return packet;
}

IProtoPacket*	AudioPacketPoolImp::newPacket(int uri, const char *data, int len, int connId)
{
	AudioPacket* proto = NULL;

	len += 2;	//add up packet header
	char* buf = new char[len];
	uint32_t header = (uri&0xF)|(len>>4);
	memcpy(buf, &header, 2);
	memcpy(buf+2, data, len);

	proto = (AudioPacket*)newPacket(buf, len, connId);
	proto->setConnId(connId);

	return proto;	
}

void	AudioPacketPoolImp::freePacket(IProtoPacket* proto)
{
	AudioPacket* packet = NULL;
	if( proto == NULL )
		return;

	packet = (AudioPacket*)proto;
	if( packet->getMemType() == AudioPacket::MEM_POOL )
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

