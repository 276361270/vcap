#ifndef	IPROTOPACKET_H
#define IPROTOPACKET_H

#include "ProtoConfig.h"

#define URI2SVID(svid)	svid&0xFF
#define		MAX_POOL_PACKET_SIZE	512
#define		MAX_PACKET_SIZE			4*1024*1024

class SESSCOMM_API IProtoPacket
{
public:
	enum PacketType
	{
		PROTO_PACKET,
		AUDIO_PACKET,
	};

	virtual ~IProtoPacket(){}
	virtual int			getConnId() = 0;
	virtual uint32_t	getUri() = 0;	
	virtual int			getLength() = 0;
	virtual int			getRes() = 0;
	virtual char*		getData() = 0;
	virtual void 		unpack(sox::Marshallable& obj) = 0;	
	virtual IProtoPacket*	clone() = 0;
};

#endif