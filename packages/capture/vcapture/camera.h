#ifndef Camera_H
#define Camera_H

#include "vcapconfig.h"

class DSFilter;
class DSPin;
class Camera
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
	Camera(DSFilter* filter);
	~Camera();

public:			
	void		setExpose(int expose);
	void		setAutoExpose();
	DSFilter*	filter() { return m_pFilter; }

private:
	void		getRanges();

private:
	DSFilter*			m_pFilter;
	DSPin*			m_pOutPin;
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