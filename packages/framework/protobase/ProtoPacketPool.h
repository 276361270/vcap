#ifndef	PROTOPACKETPOOL_H
#define PROTOPACKETPOOL_H

#include "ProtoConfig.h"
#include "IProtoPacket.h"
#include "IProtoPacketPool.h"
#include <deque>
#include <vector>

class IProtoPacket;
class ProtoPacketPoolImp;
class SESSCOMM_API ProtoPacketPool : public IProtoPacketPool
{
public:
	ProtoPacketPool();
	ProtoPacketPool(int limit);
	~ProtoPacketPool();

public:
	IProtoPacket*	newPacket(int uri, const sox::Marshallable& req);
	IProtoPacket*	newPacket(const char *data, int len, int connId);
	IProtoPacket*	newPacket(int uri, const char *data, int len, int connId);
	void			freePacket(IProtoPacket* proto);

private:
	ProtoPacketPoolImp*	m_pPoolImp;
};

#endif