#include "audiocapture.h"
#include "videocapture.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved
					  )
{
	return TRUE;
}

extern "C" __declspec(dllexport) IVCapAudioCapture* __stdcall getAudioCapture()
{
	AudioCapture* audio = new AudioCapture();
	return audio;
}

extern "C" __declspec(dllexport) IVCapVideoCapture* __stdcall getVideoCapture()
{
	VideoCapture* video = new VideoCapture();
	return video;
}