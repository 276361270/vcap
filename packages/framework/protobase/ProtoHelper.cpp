#include "ProtoHelper.h"
#include "ProtoLog.h"
#include <sstream>

const uint32_t MIN_PIP_SID = 3000000000UL;	// 30вк
const uint32_t MAX_PIP_SID = 3100000000UL;	// 31вк
const uint32_t KMaxAudioPacketSize = 16*1024; //16K

uint32_t ProtoHelper::getUri(const char* data, int len)
{
	if( !data || len < 10 )
		return 0;

	return *(uint32_t*)(data+4);
}

uint16_t ProtoHelper::getResCode(const char* data, int len)
{
	if( !data || len < 10 )
		return -1;

	return *(uint16_t*)(data+8);
}

void	ProtoHelper::unpack(const char* data, int len, sox::Marshallable& req)
{
	if( !data || len < 10 )
		return;

	sox::Unpack unpak(data+10, len-10);
	req.unmarshal(unpak);
}

void ProtoHelper::unmarshall(const char* data, int len, sox::Marshallable& req)
{
	sox::Unpack unpak(data, len);
	req.unmarshal(unpak);
}

std::string	 ProtoHelper::ProtoToString(uint32_t uri, const sox::Marshallable& req)
{
	int len = 0;
	sox::PackBuffer pb;
	sox::Pack hpk(pb);
	sox::Pack pk(pb, 10);

	req.marshal(pk);
	hpk.replace_uint32(4, uri);
	hpk.replace_uint16(8, 0xC8);

	len = 10 + pk.size();
	hpk.replace_uint32(0, len);

	return std::string( hpk.data(), len );
}

bool ProtoHelper::isAudioProto(const char* data, int len)
{
	if( len < 4 )
		return false;
	char b = data[3];
	if( b&0x80 )
		return true;
	return false;
}

bool ProtoHelper::isValidAudioProto(const char* data, int len)
{
    // get len
    uint16_t header = *((uint16_t*)data);
    header = XNTOHS(header);
    int _len = (header>>4)&0xFFF;
    if (_len == len && _len < KMaxAudioPacketSize)
    {
        return true;
    }

    //log
    PLOG("invalid audio proto packet, real len = ", len, ",unpack len = ", _len);
    return false;

}

std::string	ProtoHelper::AudioProtoToString(uint32_t uri, const sox::Marshallable& req)
{
	int len = 0;
	sox::PackBuffer pb;
	sox::Pack hpk(pb);
	sox::Pack pk(pb, 2);

	req.marshal(pk);
	len = 10 + pk.size();

	hpk.replace_uint16(0, (uri&0xF)|(len>>4));

	return std::string( hpk.data(), len );
}

uint32_t ProtoHelper::IPToUint32(const std::string& ip)
{
     return ::inet_addr( ip.c_str() );
}

std::string	ProtoHelper::IPToString(uint32_t ip)
{
    //return sox::addr_ntoa(ip);
    struct in_addr addr;
    memcpy(&addr, &ip, 4);
    return std::string(inet_ntoa(addr));
}

/*
std::string ProtoHelper::UnZipString(std::string& zip_str, uint32_t unzip_sz)
{
	std::string unzip_str("");

	if (zip_str.empty())
	{
		//PLOG("ProtoHelper::UnZipString, len = 0");
		return unzip_str;
	}

	Bytef *buf = new Bytef[unzip_sz];
	uLong dLength = unzip_sz;
	int ret = -1; 
	ret	= uncompress(buf, &dLength, (const Bytef *)zip_str.data(), (uLong)zip_str.length());

	if(ret == Z_OK)
	{
		unzip_str.assign((const char *)buf, dLength);
	}
	else
	{
		//PLOG("ProtoHelper::UnZipString, uncompress ret =", ret);
	}	

	delete[] buf;
	return unzip_str;
}
*/

bool	ProtoHelper::isPip(uint32_t sid)
{
	return (sid >= MIN_PIP_SID);
}

std::string	ProtoHelper::toString(uint32_t i)
{
	std::stringstream ss;
	ss<<i;

	return ss.str();
}

void ProtoHelper::getHostName(const char *name, std::vector<uint32_t> &out)
{
    struct hostent *hptr = gethostbyname(name);
    if(hptr)
    {
        int x = 0;
        while (hptr->h_addr_list[x] != 0)
        {
            out.push_back(*(uint32_t *) hptr->h_addr_list[x++]);
        }
        std::random_shuffle(out.begin(), out.end());
    }
}

