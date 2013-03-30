#ifndef VIDEOCAPTURE_H
#define VIDEOCAPTURE_H

#include "vcapconfig.h"

class VCapEngine;
class VCapCamera;
class VCapVMRRender;
class FfmEncoder;
class VCapFileFilter;
class VideoCapture : public IVCapVideoCapture
{
public:
	VideoCapture();
	~VideoCapture();

public:
	virtual void	setFileName(const wchar_t* filename);
	virtual void	setVideoFormat(int format);
	virtual int		startCapture(int hWnd);
	virtual int		stopCapture();
	virtual void	paint();

private:
	VCapEngine*		m_pEngine;
	std::wstring	m_wstrFileName;	
	VCapCamera*		m_pCamera;
	FfmEncoder*		m_pEncoder;		
	VCapFileFilter*	m_pFileFilter;
	VCapVMRRender*	m_pVMRRender;

	std::vector<VCapCamera*>	m_arrCameras;
};


#endif