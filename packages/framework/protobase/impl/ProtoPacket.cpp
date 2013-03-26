#include "ProtoPacket.h"
#include "ProtoLog.h"
//#include "res_code.h"

/**
 * only called by ProtoPacketPool, to create the ProtoPacket pool members.
 * the buffer will be assigned to ProtoPacket object, exclusively.
 */
ProtoPacket::ProtoPacket(char* buf, int len)
{
	_connId = -1;
	_buf = buf;
	_len = len;
	_uri = 0;
	_res = 200;
}

ProtoPacket::~ProtoPacket()
{
	if( _buf )
		delete[] _buf;
}

int	ProtoPacket::getConnId()
{
	return _connId;
}

uint32_t ProtoPacket::getUri() 
{
	return _uri;
}

int		ProtoPacket::getRes()
{	
	return _res;
}

char*	ProtoPacket::getData() 
{
	return _buf;
}

int		ProtoPacket::getLength()
{
	return _len;
}

//need-refact
void	ProtoPacket::unpack(sox::Marshallable& obj)
{
	sox::Unpack up( _buf+10, _len-10 );
	obj.unmarshal(up);
}

IProtoPacket*	ProtoPacket::clone()
{
	char*	buf = new char[_len];
	memcpy(buf, _buf, _len);
	ProtoPacket* copy = new ProtoPacket(buf, _len);
	copy->_len = _len;
	copy->_connId = _connId;
	copy->_mem_type = MEM_NEW;
    copy->_uri = _uri;
    copy->_res = _res;

	return copy;
}


/**
 * fill the buffer of ProtoPacket with a input Request object.
 * This is usually used to send packet to server.
 */
void	ProtoPacket::marshal(int uri, const sox::Marshallable& req)
{
	sox::PackBuffer pb;
	sox::Pack hpk(pb);
	sox::Pack pk(pb, 10);

	req.marshal(pk);
	hpk.replace_uint32(4, uri);
	hpk.replace_uint16(8, 0xC8);

	_len = 10 + pk.size();
	hpk.replace_uint32(0, _len);
	
	_uri = uri;	

	memcpy(_buf, hpk.data(), _len);
}

/**
 * parse the buffer into a Response object.
 * This is usually used to parse server response.
 */
void	ProtoPacket::unmarshal(const char *data, int len)
{
	sox::Unpack up(data, len);
	_len = up.pop_uint32();
	_uri = up.pop_uint32();
	_res = up.pop_uint16();

	if( _len != len )
	{
		PLOG("ProtoPacket::unmarshal, _len!=len, len/_len=", len, _len);
		return;
	}
	if( _len > MAX_PACKET_SIZE )
	{
		PLOG("ProtoPacket::unmarshal, _len is too large, len/_len=", len, _len);
		return;
	}

	memcpy(_buf, data, _len);
}

void	ProtoPacket::setMemType(MemType type)
{
	_mem_type = type;
}

ProtoPacket::MemType	ProtoPacket::getMemType()
{
	return _mem_type;
}

void	ProtoPacket::setConnId(int connId)
{
	_connId = connId;
}

void	ProtoPacket::reset()
{
	memset(_buf, 0, _len);
	_connId = -1;
}

