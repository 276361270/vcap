#ifndef	PROTOPACKET_H
#define PROTOPACKET_H

#include "ProtoConfig.h"
#include "IProtoPacket.h"

class SESSCOMM_API ProtoPacket : public IProtoPacket
{
public:
	enum MemType
	{
		MEM_POOL,
		MEM_NEW
	};

private:
	ProtoPacket(char* buf, int len);
	virtual ~ProtoPacket();

	friend class ProtoPacketPoolImp;
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