#ifndef	PROTOUTILS_H
#define PROTOUTILS_H

#include "ProtoConfig.h"
#include <vector>
#include <string>
#include <algorithm>


class ProtoUtils
{
public:
	static bool GetHostIp(const char* strLbs, std::string& strTcpIp, std::vector<uint32_t>& vecUdpIps);	
	static void	ShuffleServer(std::vector<uint32_t> ips, std::vector<uint16_t> ports);

	static int	getInteger(std::string value);
	static bool getBool(std::string value);

	static void	sleep(uint32_t millsec);
};


#endif
