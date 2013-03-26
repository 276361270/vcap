#ifndef AUDIOPACKETPOOLIMP_H
#define AUDIOPACKETPOOLIMP_H

#include "IProtoPacket.h"
#include <deque>

class IProtoPacket;
class ProtoMutex;
class AudioPacketPoolImp
{
public:
	AudioPacketPoolImp(int limit);
	~AudioPacketPoolImp();

public:
	IProtoPacket*	newPacket(int uri, const sox::Marshallable& req);
	IProtoPacket*	newPacket(const char *data, int len, int connId);
	IProtoPacket*	newPacket(int uri, const char *data, int len, int connId);
	void			freePacket(IProtoPacket* proto);
	
private:
	ProtoMutex*	mMutex;
	std::deque<IProtoPacket*>	mPackets;
	int			mLimit;

};

#endif