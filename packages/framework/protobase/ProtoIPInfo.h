#ifndef	PROTOIPINFO_H
#define PROTOIPINFO_H

#include "ProtoConfig.h"
#include <vector>

class SESSCOMM_API ProtoIPInfo
{
public:
	struct IPInfo
	{
		uint32_t ip;
		uint16_t port;
	};

	struct PortInfo
	{
		uint16_t port;
		bool	used;
	};

	struct IPRTInfo
	{		
		uint32_t	group;
		uint32_t	users;
		uint32_t	availableLoads;
		uint32_t	ispType;
		uint32_t	areaType;

		uint32_t	ip;
		std::vector<uint16_t> ports;

		bool	tcp;
		bool	used;
		bool	disabled;
		uint32_t retryTimes;
		uint32_t rtt;
	};

public:
    ProtoIPInfo();
	ProtoIPInfo(bool tcp, uint32_t ip, const std::vector<uint16_t>& ports);

public:
	uint32_t	getIP();
	const std::vector<uint16_t>& getPorts();
	

	void		setGroup(uint32_t group);
	uint32_t	getGroup();
	void		setUsers(uint32_t users);
	uint32_t	getUsers();
	void		setAvailableLoads(uint32_t avloads);
	uint32_t	getAvailableLoads();
	void		setIspType(uint32_t type);
	uint32_t	getIspType();
	void		setAreaType(uint32_t type);
	uint32_t	getAreaType();

	bool		isTcp();
	void		setUsed(bool used);
	bool		getUsed();
	void		setDisabled(bool disable);
	bool		getDisabled();
	void		incRetryTimes();
	void		clearRetryTimes();
	uint32_t	getRetryTimes();
	void		setRtt(uint32_t rtt);
	uint32_t	getRtt();

	void		reset();
    void        clone(ProtoIPInfo & ipInfo);

private:
	IPRTInfo	mIPRTInfo;

};


#endif
