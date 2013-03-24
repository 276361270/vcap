#ifndef VCAPVIDEOCAPTURE_H
#define VCAPVIDEOCAPTURE_H

#include "vcapconfig.h"

class VCapEngine;
class VCapCamera;
class VCapVMRRender;
class VCapVideoEncoder;
class VCapFileFilter;
class VCapNetFilter;
class VCapVideoCapture : public IVCapVideoCapture
{
public:
	VCapVideoCapture();
	~VCapVideoCapture();

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
	VCapVideoEncoder*	m_pEncoder;		
	VCapFileFilter*	m_pFileFilter;
	VCapNetFilter*	m_pNetFilter;
	VCapVMRRender*	m_pVMRRender;

	std::vector<VCapCamera*>	m_arrCameras;
};


#endif