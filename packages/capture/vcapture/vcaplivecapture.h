#ifndef VCAPLIVECAPTURE_H
#define VCAPLIVECAPTURE_H

#include "vcapconfig.h"

class VCapEngine;
class VCapCamera;
class VCapVMRRender;
class VCapVideoEncoder;
class VCapNetFilter;
class VCapLiveCapture : public IVCapLiveCapture
{
public:
	VCapLiveCapture();
	~VCapLiveCapture();

public:
	virtual int		startCapture(int hWnd);
	virtual int		stopCapture();
	virtual void	paint();

private:
	VCapEngine*		m_pEngine;	
	VCapCamera*		m_pCamera;
	VCapVideoEncoder*	m_pEncoder;	
	VCapNetFilter*	m_pNetFilter;
	VCapVMRRender*	m_pVMRRender;

	std::vector<VCapCamera*>	m_arrCameras;
};


#endif