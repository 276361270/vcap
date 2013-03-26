#include "ProtoIPInfo.h"
#include <algorithm>

ProtoIPInfo::ProtoIPInfo()
{
    mIPRTInfo.group = 0;
    mIPRTInfo.users = 0;
    mIPRTInfo.availableLoads = 0;
    mIPRTInfo.ispType = AUTO_DETECT;
    mIPRTInfo.areaType = AREA_UNKNOWN;

    mIPRTInfo.ip = 0;
    mIPRTInfo.ports.clear();
    mIPRTInfo.tcp = true;
    mIPRTInfo.used = false;
    mIPRTInfo.disabled = false;
    mIPRTInfo.retryTimes = 0;
    mIPRTInfo.rtt = 0;  
}

ProtoIPInfo::ProtoIPInfo(bool tcp, uint32_t ip, const std::vector<uint16_t>& ports)
{
	//memset(&mIPRTInfo, 0, sizeof(mIPRTInfo));
	
	mIPRTInfo.group = 0;
	mIPRTInfo.users = 0;
	mIPRTInfo.availableLoads = 0;
	mIPRTInfo.ispType = AUTO_DETECT;
	mIPRTInfo.areaType = AREA_UNKNOWN;

	mIPRTInfo.ip = ip;
	mIPRTInfo.ports.assign( ports.begin(), ports.end() );
	mIPRTInfo.tcp = tcp;
	mIPRTInfo.used = false;
	mIPRTInfo.disabled = false;
	mIPRTInfo.retryTimes = 0;
	mIPRTInfo.rtt = 0;
}

uint32_t	ProtoIPInfo::getIP()
{
	return mIPRTInfo.ip;
}

const std::vector<uint16_t>&	ProtoIPInfo::getPorts()
{
	return mIPRTInfo.ports;
}

bool		ProtoIPInfo::isTcp()
{
	return mIPRTInfo.tcp;
}

void		ProtoIPInfo::setUsed(bool used)
{
	mIPRTInfo.used = used;
	if( used )
	{
		mIPRTInfo.retryTimes = 0;
	}
}

bool		ProtoIPInfo::getUsed()
{
	return mIPRTInfo.used;
}

void		ProtoIPInfo::setDisabled(bool disable)
{
	mIPRTInfo.disabled = disable;
}

bool		ProtoIPInfo::getDisabled()
{
	return mIPRTInfo.disabled;
}

void		ProtoIPInfo::incRetryTimes()
{
	mIPRTInfo.retryTimes++;
}

void		ProtoIPInfo::clearRetryTimes()
{
	mIPRTInfo.retryTimes = 0;
}

uint32_t	ProtoIPInfo::getRetryTimes()
{
	return mIPRTInfo.retryTimes;
}

void		ProtoIPInfo::setGroup(uint32_t group)
{
	mIPRTInfo.group = group;
}

uint32_t	ProtoIPInfo::getGroup()
{
	return mIPRTInfo.group;
}

void		ProtoIPInfo::setUsers(uint32_t users)
{
	mIPRTInfo.users = users;
}

uint32_t	ProtoIPInfo::getUsers()
{
	return mIPRTInfo.users;
}

void		ProtoIPInfo::setAvailableLoads(uint32_t avloads)
{
	mIPRTInfo.availableLoads = avloads;
}

uint32_t	ProtoIPInfo::getAvailableLoads()
{
	return mIPRTInfo.availableLoads;
}

void		ProtoIPInfo::setIspType(uint32_t type)
{
	mIPRTInfo.ispType = type;
}

uint32_t		ProtoIPInfo::getIspType()
{
	return mIPRTInfo.ispType;
}

void		ProtoIPInfo::setAreaType(uint32_t type)
{
	mIPRTInfo.areaType = type;
}

uint32_t	ProtoIPInfo::getAreaType()
{
	return mIPRTInfo.areaType;
}

void		ProtoIPInfo::setRtt(uint32_t rtt)
{
	mIPRTInfo.rtt = rtt;
}

uint32_t	ProtoIPInfo::getRtt()
{
	return mIPRTInfo.rtt;
}

void		ProtoIPInfo::reset()
{
	mIPRTInfo.disabled = false;
	mIPRTInfo.retryTimes = 0;
}

void        ProtoIPInfo::clone(ProtoIPInfo & ipInfo)
{
    this->mIPRTInfo.ports.clear();
    this->mIPRTInfo.areaType = ipInfo.mIPRTInfo.areaType;
    this->mIPRTInfo.availableLoads = ipInfo.mIPRTInfo.availableLoads;
    this->mIPRTInfo.disabled = ipInfo.mIPRTInfo.disabled;
    this->mIPRTInfo.group = ipInfo.mIPRTInfo.group;
    this->mIPRTInfo.ip = ipInfo.mIPRTInfo.ip;
    this->mIPRTInfo.ispType = ipInfo.mIPRTInfo.ispType;
    this->mIPRTInfo.ports.assign(ipInfo.mIPRTInfo.ports.begin(), ipInfo.mIPRTInfo.ports.end());
    this->mIPRTInfo.retryTimes = ipInfo.mIPRTInfo.retryTimes;
    this->mIPRTInfo.rtt = ipInfo.mIPRTInfo.rtt;
    this->mIPRTInfo.tcp = ipInfo.mIPRTInfo.tcp;
}