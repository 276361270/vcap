#ifndef PROTOA2U_H
#define PROTOA2U_H


#include "ProtoConfig.h"
#include <string>

class SESSCOMM_API ProtoA2U
{
public:
    static void net2app(const std::string & net, wchar_t ** io);

    static std::wstring net2app(const std::string& net);

    static std::string app2net(const wchar_t * w);

    static std::string app2net(const std::wstring &w);

    static std::string addr_ntoa(u_long ip);

    static std::wstring uitow10(unsigned int i);

	static uint32_t huli_to_id(const std::wstring& hid);

	static std::wstring uid_to_huli(uint32_t uid);

    static int hex2ascii_format(char * debug_buf, int buf_max, const char * src, int len);
};


#endif
