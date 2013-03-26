#ifndef	AUDIOPACKETPOOL_H
#define AUDIOPACKETPOOL_H

#include "ProtoConfig.h"
#include "IProtoPacket.h"
#include <deque>
#include <vector>

class IProtoPacket;
class AudioPacketPoolImp;
class SESSCOMM_API AudioPacketPool
{
public:
	AudioPacketPool();
	AudioPacketPool(int limit);
	~AudioPacketPool();

public:
	IProtoPacket*	newPacket(int uri, const sox::Marshallable& req);
	IProtoPacket*	newPacket(const char *data, int len, int connId);
	IProtoPacket*	newPacket(int uri, const char *data, int len, int connId);
	void			freePacket(IProtoPacket* proto);

private:
	AudioPacketPoolImp*	m_pPoolImp;
};

#endif