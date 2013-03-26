#ifndef	PROTOIPMGR_H
#define PROTOIPMGR_H

#include "ProtoConfig.h"
#include <vector>

class ProtoContext;
class ProtoIPInfo;
class SESSCOMM_API  ProtoIPMgr
{
public:
	enum Policy
	{
		POLICY_FIRST		= 0x00000001,
		POLICY_IGNORE_ISP	= 0x00000002,
		POLICY_IGNORE_AREA	= 0x00000004,
		POLICY_IGNORE_RETRYTIMES = 0x00000008,	
		POLICY_IGNORE_GROUP	= 0x000000010,
		POLICY_IGNORE_USED  = 0x000000020,
		
		POLICY_LOW_RTT		= 0x000000040,
		POLICY_LOW_RETRY_TIMES = 0x00000080,
		POLICY_LOW_USERS	= 0x00000100,
	};

public:
	ProtoIPMgr(uint32_t isp, uint32_t area);
	~ProtoIPMgr();

public:
	void		setIspType(uint32_t isp);
	void		setAreaType(uint32_t area);
	void		add(ProtoIPInfo* info);
    void        append(ProtoIPInfo* info);
	void		remove(ProtoIPInfo* info);
	ProtoIPInfo*find(ProtoIPInfo* info);
	ProtoIPInfo*find(uint32_t ip, bool tcp);
	uint32_t	getGroup(uint32_t ip, bool tcp);
	void		clear();
	int			getCount();

	void		reset();
	void		setUsed(ProtoIPInfo* info, bool used);
	void		incRetryTimes(ProtoIPInfo* info);
	void		clearRetryTimes(ProtoIPInfo* info);

	ProtoIPInfo* getUsed();
	ProtoIPInfo* getUnused();
	ProtoIPInfo* getUnused(bool tcp);
	ProtoIPInfo* getUnused(bool tcp, int policy);

protected:
    std::vector<ProtoIPInfo*>	mIPInfos;
private:
	std::vector<ProtoIPInfo*>	mUsedIPInfos;
	uint32_t	mIspType;
	uint32_t	mAreaType;
};


#endif