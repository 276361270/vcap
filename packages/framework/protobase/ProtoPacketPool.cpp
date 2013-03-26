#include "ProtoPacketPool.h"
#include "impl/ProtoPacketPoolImp.h"

#define		MAX_512B_PACKETS_POOL	20


ProtoPacketPool::ProtoPacketPool()
{
	m_pPoolImp = new ProtoPacketPoolImp(MAX_512B_PACKETS_POOL);
}

ProtoPacketPool::ProtoPacketPool(int limit)
{
	m_pPoolImp = new ProtoPacketPoolImp(limit);
}

ProtoPacketPool::~ProtoPacketPool()
{
	if( m_pPoolImp )
		delete m_pPoolImp;
}

IProtoPacket*	ProtoPacketPool::newPacket(int uri, const sox::Marshallable& req)
{
	return m_pPoolImp->newPacket(uri, req);
}

IProtoPacket*	ProtoPacketPool::newPacket(const char *data, int len, int connId)
{
	return m_pPoolImp->newPacket(data, len, connId);
}

IProtoPacket*	ProtoPacketPool::newPacket(int uri, const char *data, int len, int connId)
{
	return m_pPoolImp->newPacket(uri, data, len, connId);
}

void	ProtoPacketPool::freePacket(IProtoPacket* proto)
{
	return m_pPoolImp->freePacket(proto);
}

