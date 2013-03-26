#include "ProtoTime.h"

#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#else
#include <sys/time.h>
#endif

static uint32_t s_nLastTime = 0;
uint32_t	ProtoTime::currentSystemTime()
{
#ifdef _WIN32
	uint32_t t = timeGetTime();
#else
    struct timeval curTime;
    gettimeofday(&curTime, NULL);
    uint32_t t = (curTime.tv_sec * 1000) + (curTime.tv_usec / 1000);
#endif
	if ( t == 0 )
		t = s_nLastTime;
	s_nLastTime = t;
	return t;
}

