#include "vcapaudiocapture.h"
#include "vcapvideocapture.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved
					  )
{
	return TRUE;
}

extern "C" __declspec(dllexport) IVCapAudioCapture* __stdcall getAudioCapture()
{
	VCapAudioCapture* audio = new VCapAudioCapture();
	return audio;
}

extern "C" __declspec(dllexport) IVCapVideoCapture* __stdcall getVideoCapture()
{
	VCapVideoCapture* video = new VCapVideoCapture();
	return video;
}