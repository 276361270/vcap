#ifndef VCAPENGINE_H
#define VCAPENGINE_H


#include "vcapconfig.h"

class VCapFilter;
class VCapCamera;
class VCapVideoEncode;
class VCapVMRRender;
class VCapEngine
{
public:
	VCapEngine();
	~VCapEngine();

public:
	void	init();
	//void	startCaptureAudio(const std::wstring& filename);
	//void	stopCaptureAudio();

public:
	ICaptureGraphBuilder2*	getCaptureBuilder() { return m_pCaptureBuilder; }
	IGraphBuilder*	getGraphBuilder() { return m_pGraphBuilder; }
	IMediaControl*	getMediaControl() { return m_pMediaControl; }
	

private:	
	ICaptureGraphBuilder2*	m_pCaptureBuilder;
	IGraphBuilder*	m_pGraphBuilder;	
	IMediaControl*	m_pMediaControl;
};

#endif