#include "ProtoUtils.h"
#include "ProtoA2U.h"

#ifdef _WIN32
#include <winsock2.h>
#endif

#include <algorithm>
#include <time.h>


bool ProtoUtils::GetHostIp(const char* strLbs, std::string& strTcpIp, std::vector<uint32_t>& vecUdpIps)
{
	std::vector<uint32_t> vecIps;

	struct hostent *hptr = gethostbyname(strLbs);
	if(!hptr)
	{
	}
	else
	{
		int x = 0;
		while (hptr->h_addr_list[x] != 0) 
		{
			vecIps.push_back(*(uint32_t *) hptr->h_addr_list[x++]);
		}
	}

	if (vecIps.empty())
	{
		return false;
	}

	time_t uTime = time(NULL);
	std::vector<uint32_t>::iterator it = vecIps.begin() + ( ++uTime % vecIps.size() );
	//strTcpIp = sox::addr_ntoa(*it);
	strTcpIp = ProtoA2U::addr_ntoa(*it);
	
	int i = 2;
	while (i--)
	{
		it = vecIps.begin() + ( ++uTime % vecIps.size() );
		//vecUdpIps.push_back(sox::addr_ntoa(*it));
		vecUdpIps.push_back(*it);
	}

	return true;
}

void	ProtoUtils::ShuffleServer(std::vector<uint32_t> ips, std::vector<uint16_t> ports)
{
	std::random_shuffle(ips.begin(), ips.end());
	std::random_shuffle(ports.begin(), ports.end());
}

int		ProtoUtils::getInteger(std::string value)
{
	return atoi( value.c_str() );
}

bool	ProtoUtils::getBool(std::string value)
{
	int v = ProtoUtils::getInteger(value);
	return (v!=0);
}


void	ProtoUtils::sleep(uint32_t millsec)
{
#ifdef _WIN32
	::Sleep(millsec);
#else
    sleep(millsec);
#endif
}
