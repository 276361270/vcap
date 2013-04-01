#ifndef IVCAPENGINE_H
#define IVCAPENGINE_H

#include <Windows.h>

enum VCAP_ERROR
{
	VCAP_ERROR_OK					= 0,
	VCAP_ERROR_UNKNOWN				= 1,
	VCAP_ERROR_NO_CAMERA			= 100,
	VCAP_ERROR_NO_X264_FILTER		= 101,	
	VCAP_ERROR_NO_VMR9_SUPPORT		= 102,

	VCAP_ERROR_NO_SPEEX_FILTER		= 201,
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
	virtual int		startCapture() = 0;
	virtual int		stopCapture() = 0;
};

struct IVCapVideoCapture
{
	virtual void	setFileName(const wchar_t* filename) = 0;
	virtual void	setVideoFormat(int format) = 0;
	virtual int		startCapture(int hWnd) = 0;
	virtual int		stopCapture() = 0;
	virtual void	paint() = 0;
};

struct IVCapLiveCapture
{
	virtual int		startCapture(int hWnd) = 0;
	virtual int		stopCapture() = 0;
	virtual void	paint() = 0;
};


#endif