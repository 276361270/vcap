#ifndef FFMUTIL_H
#define FFMUTIL_H

class FfmUtil
{
public:
	static int	currentSystemTime() {
		static uint32_t s_nLastTime = 0;
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
};

#endif