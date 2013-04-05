#include "livecapture.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved
					  )
{
	return TRUE;
}

extern "C" __declspec(dllexport) IVCapLiveCapture* __stdcall getLiveCapture()
{
	LiveCapture* audio = new LiveCapture();
	return audio;
}