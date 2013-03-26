#ifndef PROTOPACKETPOOLIMP_H
#define PROTOPACKETPOOLIMP_H

#include "IProtoPacket.h"
#include <deque>

class IProtoPacket;
class ProtoMutex;
class ProtoPacketPoolImp
{
public:
	ProtoPacketPoolImp(int limit);
	~ProtoPacketPoolImp();

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