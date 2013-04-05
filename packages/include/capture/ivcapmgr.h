#ifndef IVCAPMGR_H
#define IVCAPMGR_H

#include "ivcapengine.h"
#include <stdio.h>

inline IVCapLiveCapture*	loadLiveCapture()
{
	HMODULE hModule = LoadLibraryA("vcapture.dll");
	if( !hModule || hModule == INVALID_HANDLE_VALUE )
	{
		DWORD ret = GetLastError();
		printf("loadAudioCapture failed with code: %d\r\n", ret);
		return NULL;
	}

	typedef IVCapLiveCapture* (__stdcall *GETLIVEAPTURE_FUNC)();
	GETLIVEAPTURE_FUNC func = (GETLIVEAPTURE_FUNC)GetProcAddress(hModule, "_getLiveCapture@0");
	if( !func )
		return NULL;

	return func();
}

#endif