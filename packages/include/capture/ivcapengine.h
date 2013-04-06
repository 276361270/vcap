#ifndef IVCAPENGINE_H
#define IVCAPENGINE_H

#include <Windows.h>

enum VCAP_ERROR
{
	VCAP_ERROR_OK					= 0,
	VCAP_ERROR_UNKNOWN				= 1,

	//10*, hardware relative
	VCAP_ERROR_NO_CAMERA			= 100,
	VCAP_ERROR_NO_MIC				= 101,
	
	//20*, codec relative
	VCAP_AAC_NOT_FOUND				= 200,
	VCAP_H264_NOT_FOUND				= 201,
	VCAP_AAC_OPEN_FAIL				= 202,
	VCAP_H264_OPEN_FAIL				= 203,
};

enum VCAP_AUDIO_FORMAT
{
	VCAP_AUDIO_FORMAT_SPEEX,
	VCAP_AUDIO_FORMAT_VORBIS,
};

enum VCAP_VIDEO_FORMAT
{
	VCAP_VIDEO_FORMAT_H264			= 1,
	VCAP_VIDEO_FORMAT_VP8			= 2,	
};

struct IVCapAudioCapture
{
	virtual void	setFileName(const wchar_t* filename) = 0;
	virtual void	setServer(char* ip, int port, char* app, char* stream) = 0;
	virtual int		startCapture() = 0;
	virtual int		stopCapture() = 0;
};

struct IVCapVideoCapture
{
	virtual void	setFileName(const wchar_t* filename) = 0;
	virtual void	setServer(char* ip, int port, char* app, char* stream) = 0;
	virtual int		startCapture(int hWnd) = 0;
	virtual int		stopCapture() = 0;
	virtual void	paint() = 0;
};

struct IVCapLiveCapture
{
	virtual void	setAudioServer(char* ip, int port, char* app, char* stream) = 0;
	virtual void	setVideoServer(char* ip, int port, char* app, char* stream) = 0;
	virtual int		startCapture(int hWnd) = 0;
	virtual int		stopCapture() = 0;
	virtual void	paint() = 0;
};


#endif