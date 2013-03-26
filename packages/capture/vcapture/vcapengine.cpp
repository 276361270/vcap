#include "vcapengine.h"
#include "vcapvmrrender.h"
#include "vcapfilter.h"


#pragma comment(lib, "Strmiids.lib")

VCapEngine::VCapEngine()
{
	m_pCaptureBuilder = NULL;
	m_pGraphBuilder = NULL;
	m_pMediaControl = NULL;

	::CoInitialize(NULL);
	init();
}

VCapEngine::~VCapEngine()
{
	::CoUninitialize();
}

void	VCapEngine::init()
{
	HRESULT hr = S_OK;
	::CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC, __uuidof(ICaptureGraphBuilder2), (LPVOID*)&m_pCaptureBuilder);
	::CoCreateInstance(CLSID_FilterGraph, 0, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&m_pGraphBuilder);
	m_pCaptureBuilder->SetFiltergraph(m_pGraphBuilder);
	m_pGraphBuilder->QueryInterface(IID_IMediaControl,(void**)&m_pMediaControl);	
}