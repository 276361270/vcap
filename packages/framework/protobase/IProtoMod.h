#ifndef	ISESSIONMOD_H
#define ISESSIONMOD_H

#include "ProtoConfig.h"
#include "channel/sessrequest.h"
#include "channel/sessquery.h"
#include "channel/isession.h"
//#include "common/protocol/iservicemanager.h"

class IProtoPacket;
class SESSCOMM_API IProtoMod
{
public:
	enum ModType
	{
		MOD_AUDIO,
		MOD_VIDEO,
		MOD_SERVICE,
		MOD_INFO,
		MOD_PLUGIN
	};

public:
	virtual ~ISessionMod(){}
	virtual int		getUriCount() = 0;
	virtual void	getUriList(uint32_t svids[]) = 0;
	virtual int		getReqCount() = 0;
	virtual void	getReqList(uint32_t reqs[]) = 0;
	virtual int		getModType() = 0;
	virtual void	onProto(uint32_t sid, IProtoPacket* proto) = 0;	
	virtual void	onRequest(uint32_t sid, protocol::session::SessRequest* req) = 0;
	virtual void	querySessInfo(uint32_t sid, protocol::session::SessQueryType type, void** info, uint32_t pid=0, uint32_t uid=0) = 0;
	virtual void	onLeave(uint32_t sid) = 0;
};

class SESSCOMM_API ISInfoMod : public IProtoMod
{
public:
	virtual uint32_t getCur(uint32_t sid) = 0;
	virtual bool	checkRuler(uint32_t sid, int code, uint32_t user, uint32_t room) = 0;
	virtual uint32_t getRoler(uint32_t sid, uint32_t uid, uint32_t pid) = 0;
};

class SESSCOMM_API IAudioMod : public IProtoMod
{
public:
    virtual protocol::session::IAudioSession* getAudioSession(uint32_t sid) = 0;
};


class SESSCOMM_API IServiceMod : public IProtoMod
{
public:
	//virtual protocol::service::IServiceManager* getServiceManager() = 0;
    virtual protocol::session::ISvcTransptMgr * getSvcTransptMgr(uint32_t sid) = 0;
};


#endif
