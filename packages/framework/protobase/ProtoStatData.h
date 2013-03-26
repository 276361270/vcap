#ifndef PROTOSTATDATA_H
#define PROTOSTATDATA_H

#include "ProtoConfig.h"
#include <map>

class ProtoStatDataImp;
class SESSCOMM_API ProtoStatData
{
public:
	enum ProbeType
	{
		STAT_JOIN_SESSION_START = 0,
		STAT_JOIN_SESSION_FINISH,

		//smgr
		STAT_SMANAGER_LOCATE_START,
		STAT_SMANAGER_LOCATE_FINISH,
        STAT_SMANAGER_LOOKUP_STATUS,

		//signal
		STAT_LOGIN_SIGNAL_PROXY_START,
		STAT_LOGIN_SIGNAL_PROXY_FINISH,
        STAT_LOGIN_SIGNAL_PROXY_SID_STATUS,

		//media:
		STAT_GET_MEDIA_ADDR_START,
		STAT_GET_MEDIA_ADDR_FINISH,
		STAT_LOGIN_MEDIA_PROXY_START,
		STAT_LOGIN_MEDIA_PROXY_FINISH,
		STAT_MEDIA_RECV_FIRST_VOICE,
		STAT_MEDIA_PLAY_FIRST_VOICE,


		//sinfo
		STAT_SINFO_SESS_QUERY_START,
		STAT_SINFO_SESS_QUERY_FINISH,
		STAT_SINFO_QUERY_RETRY,
		STAT_SINFO_ZIP_SIZE,
		STAT_SINFO_BASE_SIZE,
		STAT_SINFO_ADDITIONAL_SIZE,
		STAT_SINFO_TOTAL_SIZE,


        //serivce

        STAT_SVC_LOGIN_BC_START,
        STAT_SVC_LOGIN_BC_FINISH,
        STAT_SVC_LOGIN_SINFO_START,
        STAT_SVC_LOGIN_SINFO_FINISH,
        STAT_SVC_SINFO_QUERY_START,
        STAT_SVC_SINFO_QUERY_FINISH,
		//uinfo:
		STAT_GET_PARTNER_UINFO_START,
		STAT_GET_PARTNER_UINFO_FINISH,

		STAT_GET_PARTNER_UINFO_FIRST,

		//mic:
		STAT_MIC_SYNC_START,
		STAT_MIC_SYNC_FINISH,
		STAT_MIC_SYNC_COUNT,

		//roler:
		STAT_GET_FIRST_ROLE_FINISH,

		//visitor
		STAT_PUSH_PARTNER_UIDS_FINISH,
		STAT_PUSH_PARTNER_UIDS_COUNT,

		//cache
		STAT_SINFO_CACHE_LOAD_START,
		STAT_SINFO_CACHE_LOAD_FINISH,
		STAT_SINFO_CACHE_UPDATE_START,
		STAT_SINFO_CACHE_UPDATE_FINISH,		
		STAT_SINFO_CACHE_LOADED,
		STAT_SINFO_CACHE_EXPIRED,

        //service sinfo stat report via http
        STAT_CLIENT_ISP_TYPE,
        STAT_SIGNAL_PROXY_IP,
        STAT_SIGNAL_PROXY_PORT,
        STAT_SVC_SINFO_ERRCODE,
        STAT_SVC_SINFO_PROXY_IP,
        STAT_SVC_SINFO_PROXY_PORT,
        STAT_SVC_SINFO_FIRST_GROUP,
        STAT_SVC_SINFO_SECOND_GROUP,
        STAT_SVC_SINFO_PROXY_RETRYS

	};
public:
	static ProtoStatData*	getInstance();
	static void	release();

private:
	ProtoStatData();
	~ProtoStatData();

public:
	void		rebind(uint32_t sid, uint32_t asid);
	void		probeTime(uint32_t sid, uint32_t key);
	uint32_t	getTime(uint32_t sid, uint32_t key);
	uint32_t	getSpendTime(uint32_t sid, uint32_t key1, uint32_t key2);
    uint32_t    getSpendTimeUp2Now(uint32_t sid, uint32_t key);

	void		setInt(uint32_t sid, uint32_t type, uint32_t value);
	uint32_t	getInt(uint32_t sid, uint32_t type);
	void		setString(uint32_t sid, uint32_t type, std::string value);
	std::string getString(uint32_t sid, uint32_t type);

	bool		has(uint32_t sid, uint32_t key);
	void		reset(uint32_t sid);

private:
	static ProtoStatData*	s_pStatData;
	ProtoStatDataImp*	m_pStatImp;
};

#define		PROTO_STAT_REBIND(sid, asid)			ProtoStatData::getInstance()->rebind(sid, asid)
#define		PROTO_STAT_SET_TIME(sid, key)			ProtoStatData::getInstance()->probeTime(sid, key)
#define		PROTO_STAT_SET_INT(sid, key, value)		ProtoStatData::getInstance()->setInt(sid, key, value)
#define		PROTO_STAT_HAS(sid, key)				ProtoStatData::getInstance()->has(sid, key)
#define		PROTO_STAT_GET_SPEND_TIME(sid, key1, key2)	        ProtoStatData::getInstance()->getSpendTime(sid, key1, key2)
#define     PROTO_STAT_GET_SPEND_TIME_UP2NOW(sid, key)          ProtoStatData::getInstance()->getSpendTimeUp2Now(sid, key);  
#define		PROTO_STAT_GET_INT(sid, key1)	ProtoStatData::getInstance()->getInt(sid, key1)


#endif