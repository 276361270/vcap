#ifndef VCAPCAMERA_H
#define VCAPCAMERA_H

#include "vcapconfig.h"

class VCapFilter;
class VCapPin;
class VCapCamera
{
public:
	struct Property
	{
		long	min;
		long	max;
		long	step;
		long	def;
		long	flags;
	};

public:
	VCapCamera(VCapFilter* filter);
	~VCapCamera();

public:			
	void		setExpose(int expose);
	void		setAutoExpose();
	VCapFilter*	filter() { return m_pFilter; }

private:
	void		getRanges();

private:
	VCapFilter*			m_pFilter;
	VCapPin*			m_pOutPin;
	IAMCameraControl*	m_pCameraControl;
	IAMStreamConfig*	m_pStreamConfig;	
	GUID				m_guidType;
	GUID				m_guidSubType;
	GUID				m_guidFormat;
	VIDEOINFOHEADER		m_videoInfoHeader;	
	Property			m_propExpose;
	Property			m_propZoon;
	Property			m_propIris;

};

#endif