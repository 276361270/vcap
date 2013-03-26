#include "AudioPacketPool.h"
#include "impl/AudioPacketPoolImp.h"

#define		MAX_512B_PACKETS_POOL	20


AudioPacketPool::AudioPacketPool()
{
	m_pPoolImp = new AudioPacketPoolImp(MAX_512B_PACKETS_POOL);
}

AudioPacketPool::AudioPacketPool(int limit)
{
	m_pPoolImp = new AudioPacketPoolImp(limit);
}

AudioPacketPool::~AudioPacketPool()
{
	if( m_pPoolImp )
		delete m_pPoolImp;
}

IProtoPacket*	AudioPacketPool::newPacket(int uri, const sox::Marshallable& req)
{
	return m_pPoolImp->newPacket(uri, req);
}

IProtoPacket*	AudioPacketPool::newPacket(const char *data, int len, int connId)
{
	return m_pPoolImp->newPacket(data, len, connId);
}

IProtoPacket*	AudioPacketPool::newPacket(int uri, const char *data, int len, int connId)
{
	return m_pPoolImp->newPacket(uri, data, len, connId);
}

void	AudioPacketPool::freePacket(IProtoPacket* proto)
{
	return m_pPoolImp->freePacket(proto);
}

