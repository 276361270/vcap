#ifndef _LIVECAPTURE_H
#define _LIVECAPTURE_H

#include "vcapconfig.h"

class Engine;
class Camera;
class VMRRender;
class FfmEncoder;
class VideoCapture;
class AudioCapture;
class LiveCapture : public IVCapLiveCapture
{
public:
	LiveCapture();
	~LiveCapture();

public:
	virtual int		startCapture(int hWnd);
	virtual int		stopCapture();
	virtual void	paint();

private:
	VideoCapture*	m_pVideoCapture;
	AudioCapture*	m_pAudioCapture;
};


#endif