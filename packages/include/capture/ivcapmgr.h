#ifndef IVCAPMGR_H
#define IVCAPMGR_H

#include "ivcapengine.h"
#include <stdio.h>

inline IVCapAudioCapture*	loadAudioCapture()
{
	HMODULE hModule = LoadLibraryA("vcapture.dll");
	if( !hModule || hModule == INVALID_HANDLE_VALUE )
	{
		DWORD ret = GetLastError();
		printf("loadAudioCapture failed with code: %d\r\n", ret);
		return NULL;
	}

	typedef IVCapAudioCapture* (__stdcall *GETAUDIOCAPTURE_FUNC)();
	GETAUDIOCAPTURE_FUNC func = (GETAUDIOCAPTURE_FUNC)GetProcAddress(hModule, "_getAudioCapture@0");
	if( !func )
		return NULL;

	return func();
}

inline IVCapVideoCapture*	loadVideoCapture()
{
	HMODULE hModule = LoadLibraryA("vcapture.dll");
	if( !hModule || hModule == INVALID_HANDLE_VALUE )
		return NULL;


	typedef IVCapVideoCapture* (__stdcall *GETVIDEOCAPTURE_FUNC)();
	GETVIDEOCAPTURE_FUNC func = (GETVIDEOCAPTURE_FUNC)GetProcAddress(hModule, "_getVideoCapture@0");
	if( !func )
		return NULL;

	return func();
}

#endif