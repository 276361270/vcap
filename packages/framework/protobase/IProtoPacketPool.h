#ifndef	IPROTOPACKETPOOL_H
#define IPROTOPACKETPOOL_H

class SESSCOMM_API IProtoPacketPool
{
public:
	virtual IProtoPacket*	newPacket(int uri, const sox::Marshallable& req) = 0;
	virtual IProtoPacket*	newPacket(const char *data, int len, int connId) = 0;
	virtual IProtoPacket*	newPacket(int uri, const char *data, int len, int connId) = 0;
	virtual void			freePacket(IProtoPacket* proto) = 0;
};

#endif
