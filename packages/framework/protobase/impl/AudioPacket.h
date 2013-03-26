#ifndef AUDIOPACKET_H
#define AUDIOPACKET_H

#include "IProtoPacket.h"

//uri | len 
//4     12	
class AudioPacket : public IProtoPacket
{
public:
	enum MemType
	{
		MEM_POOL,
		MEM_NEW
	};

private:
	AudioPacket(char* buf, int len);
	virtual ~AudioPacket();

	friend class AudioPacketPoolImp;
public:
	virtual int			getConnId();
	virtual uint32_t	getUri() ;	
	virtual int			getLength();
	virtual int			getRes();
	virtual char*		getData();
	virtual void		unpack(sox::Marshallable& obj);
	virtual IProtoPacket*	clone();

public:
	void	marshal(int uri, const sox::Marshallable& req);
	void	unmarshal(const char *data, int len);
	void	setMemType(MemType type);
	MemType	getMemType();
	void	setConnId(int connId);
	void	reset();		

private:
	int		_connId;
	char*	_buf;
	int		_len;
	int		_uri;
	int		_res;
	MemType	_mem_type;
};


#endif