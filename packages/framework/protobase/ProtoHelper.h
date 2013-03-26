#ifndef PROTOHELPER_H
#define PROTOHELPER_H

#include "ProtoConfig.h"
#include <string>

class SESSCOMM_API ProtoHelper
{
public:
	static uint32_t getUri(const char* data, int len);
    static uint32_t IPToUint32(const std::string& ip);
	static uint16_t getResCode(const char* data, int len);
	static void unpack(const char* data, int len, sox::Marshallable& req);
	static void unmarshall(const char* data, int len, sox::Marshallable& req);
	static std::string	ProtoToString(uint32_t uri, const sox::Marshallable& req);
	static bool isAudioProto(const char* data, int len);
    static bool isValidAudioProto(const char* data, int len);
	static std::string	AudioProtoToString(uint32_t uri, const sox::Marshallable& req);
	static std::string	IPToString(uint32_t ip);
	//static std::string	UnZipString(std::string& zip_str, uint32_t unzip_sz);
	static bool	isPip(uint32_t sid);
	static std::string	toString(uint32_t i);
    static void getHostName(const char *name, std::vector<uint32_t> &out);
};

#endif