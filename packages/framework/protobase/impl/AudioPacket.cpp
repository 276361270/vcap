#include "AudioPacket.h"

/**
 * only called by ProtoPacketPool, to create the ProtoPacket pool members.
 * the buffer will be assigned to ProtoPacket object, exclusively.
 */
AudioPacket::AudioPacket(char* buf, int len)
{
	_connId = -1;
	_buf = buf;
	_len = len;
	_uri = 0;
	_res = 200;
}

AudioPacket::~AudioPacket()
{
	if( _buf )
		delete[] _buf;
}

int	AudioPacket::getConnId()
{
	return _connId;
}

uint32_t AudioPacket::getUri() 
{
	return _uri;
}

int		AudioPacket::getRes()
{	
	return _res;
}

char*	AudioPacket::getData() 
{
	return _buf;
}

int		AudioPacket::getLength()
{
	return _len;
}

//need-refact
void	AudioPacket::unpack(sox::Marshallable& obj)
{
	sox::Unpack up( _buf+2, _len-2 );
	obj.unmarshal(up);
}

IProtoPacket*	AudioPacket::clone()
{
	char*	buf = new char[_len];
	memcpy(buf, _buf, _len);
	AudioPacket* copy = new AudioPacket(buf, _len);
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
void	AudioPacket::marshal(int uri, const sox::Marshallable& req)
{
	sox::PackBuffer pb;
	sox::Pack hpk(pb);
	sox::Pack pk(pb, 2);

	req.marshal(pk);
	//hpk.replace_uint32(4, uri);
	//hpk.replace_uint16(8, 0xC8);

	_len = 2 + pk.size();	
	_uri = uri;	

	hpk.replace_uint16(0, (_uri&0xF)|((uint16_t)_len<<4));

	memcpy(_buf, hpk.data(), _len);
}

/**
 * parse the buffer into a Response object.
 * This is usually used to parse server response.
 */
void	AudioPacket::unmarshal(const char *data, int len)
{
	sox::Unpack up(data, len);
	uint32_t header = up.pop_uint16();
	_len = (header>>4)&0xFFF;
	_uri = header&0xF;

	memcpy(_buf, data, _len);
}

void	AudioPacket::setMemType(MemType type)
{
	_mem_type = type;
}

AudioPacket::MemType	AudioPacket::getMemType()
{
	return _mem_type;
}

void	AudioPacket::setConnId(int connId)
{
	_connId = connId;
}

void	AudioPacket::reset()
{
	memset(_buf, 0, _len);
	_connId = -1;
}

