#include "ProtoA2U.h"


void ProtoA2U::net2app(const std::string & net, wchar_t ** io)
{
#ifdef  _WIN32
    int chars = int(net.size());
    int out_len = 0;
    wchar_t* buf = NULL;

    out_len = MultiByteToWideChar(CP_UTF8, 0, net.c_str(), chars, NULL, 0)+1;
    if( out_len == 0 )
    {
        //we have a fail here, make an big buffer:
        out_len = chars*4;
    }
    buf = new wchar_t[out_len];
    memset(buf, 0, out_len*sizeof(wchar_t));

    int ret = MultiByteToWideChar(CP_UTF8, 0, net.data(), chars, buf, out_len*sizeof(wchar_t));
    if( ret == 0 )
    {
        //still fail
        delete[] buf;
        *io = NULL;
        return;
    }

    *io = buf;

#else
    //not of good performance, need improve later.
    //create a singleton object.
    const char* inbuf = net.c_str();
    size_t chars = int(net.size());
    size_t out_len = 0;
	wchar_t* buf = NULL;
    size_t num = 0;

	*io = NULL;
	iconv_t icv = iconv_open("UNICODE", "UTF-8");
    if( icv == (iconv_t)-1 )
		return;

	out_len = chars*2;
    buf = new wchar_t[out_len/2];
    num = iconv(icv, (char**)&inbuf, &chars, (char**)&buf, &out_len);
    iconv_close(icv);
	if( num == -1 )
	{
		delete[] buf;
		return;
	}
	*io = buf;
#endif
}

std::wstring ProtoA2U::net2app(const std::string& net)
{
    wchar_t* buf = NULL;

    net2app(net, &buf);
    if( buf == NULL )
        return std::wstring(L"");

    std::wstring ret(buf);
    delete[] buf;

    return ret;
}

std::string ProtoA2U::app2net(const wchar_t * w)
{
#ifdef _WIN32
    char* buf = NULL;
    if (!w)
        return std::string();
    // utf16 -> utf8

    // 计算大小
    int size = WideCharToMultiByte(CP_UTF8, 0, w, -1, NULL, NULL, NULL, NULL) + 1;

    if( size == 0 )
        return "";
    // 转换
    buf = new char[size];
    memset(buf, 0, size);
    WideCharToMultiByte(CP_UTF8, 0, w, -1, buf, size, NULL, NULL);

    std::string str(buf);
    delete[] buf;

    return str;
#else
    //not of good performance, need improve later.
    //create a singleton object.
	char* buf = NULL;
	if( !w )
		return std::string();
    size_t size = wcslen(w)*sizeof(wchar_t);
    size_t out_len = size*3;
    size_t num = 0;

	iconv_t icv = iconv_open("UTF-8", "UNICODE");
    if( icv == (iconv_t)-1 )
		return "";

	buf = new char[out_len];
	memset(buf, 0, out_len);
    num = iconv(icv, (char**)&w, &size, &buf, &out_len);
    iconv_close(icv);

    if( num == -1 )
	{
		delete[] buf;
		return "";
	}

	std::string str(buf);
	delete []buf;

	return str;

#endif
}

std::string ProtoA2U::app2net(const std::wstring &w)
{
    return app2net(w.data());
}

std::string ProtoA2U::addr_ntoa(u_long ip)
{
    struct in_addr addr;
    memcpy(&addr, &ip, 4);
    return std::string(::inet_ntoa(addr));
}

std::wstring ProtoA2U::uitow10(unsigned int i)
{
    wchar_t buf[20];
    swprintf(buf, 20, L"%u", i);
    return std::wstring(buf);
}

uint32_t ProtoA2U::huli_to_id(const std::wstring& hid)
{
	uint32_t ret = 0;
	const wchar_t* szHid = hid.c_str();

	while(*szHid  && *szHid != L'_')
	{
		int num = *szHid - L'0';
		if (num >= 0 && num <= 9)
		{
			ret *= 10;
			ret += num;
		}
		else
		{
			break;
		}
		++szHid;
	}

	if(ret == 0)
	{
		return INVALID_UID;
	}else{
		return ret;
	}
}

std::wstring ProtoA2U::uid_to_huli(uint32_t uid)
{
	std::wstring strUid = ProtoA2U::uitow10(uid);
	strUid.append(L"_@U");
	return strUid;
	/*
	static const size_t bufsize = 20;
	wchar_t buf[bufsize] = {0};
	const wchar_t* szHuli = buf;

	int idx = bufsize - 5;
	unsigned int temp = uid;
	while((temp != 0) && (idx >= 0))
	{
		buf[idx] = temp % 10 + L'0';
		temp /= 10;
		--idx;
	}
	buf[bufsize - 4] = L'_';
	buf[bufsize - 3] = L'@';
	buf[bufsize - 2] = L'U';
	if (idx >= 0)
	{
		szHuli += (idx + 1);
	}

	std::wstring strUid;
	strUid.assign(szHuli, (bufsize-idx-1)*sizeof(wchar_t));
	return strUid;
	*/
}

int ProtoA2U::hex2ascii_format(char * debug_buf, int buf_max,
    const char * src, int len)
{
    int i;
    const unsigned char * psrc = (const unsigned char *)src;

    unsigned char tmp;
    char hex2ascii[] = "0123456789ABCDEF";

    for(i=0; 2*i+1<buf_max && i<len; i++)
    {
        tmp = *(psrc+i);
        debug_buf[2*i] = hex2ascii[(tmp>>4)&0xF];
        debug_buf[2*i+1] = hex2ascii[tmp&0xF];
    }

    return 2*i;
}
