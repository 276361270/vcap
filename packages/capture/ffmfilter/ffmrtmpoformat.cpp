#include "ffmrtmpoformat.h"

FfmRtmpOFormat::FfmRtmpOFormat(char* ip, int port, char* app, char* stream)
{
	char url[MAX_PATH];
	memset(url, 0, MAX_PATH);
	sprintf(url, "rtmp://%s:%d/%s/%s", ip, port, app, stream);
	init("flv", url);
}