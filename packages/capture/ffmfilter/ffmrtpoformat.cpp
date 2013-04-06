#include "ffmrtpoformat.h"

FfmRtpOFormat::FfmRtpOFormat(char* ip, int port, char* app, char* stream)
{
	char url[MAX_PATH];
	memset(url, 0, MAX_PATH);
	sprintf(url, "rtp://%s:%d/%s/%s", ip, port, app, stream);
	init("rtp", url);
}