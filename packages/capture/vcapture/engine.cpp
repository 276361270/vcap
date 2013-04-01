#include "engine.h"
#include "vmrrender.h"
#include "dsfilter.h"


#pragma comment(lib, "Strmiids.lib")

Engine::Engine()
{
	m_pCaptureBuilder = NULL;
	m_pGraphBuilder = NULL;
	m_pMediaControl = NULL;
	m_bStarted = false;
	::CoInitialize(NULL);
	init();
}

Engine::~Engine()
{
	::CoUninitialize();
}

void	Engine::init()
{
	HRESULT hr = S_OK;
	hr = ::CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC, __uuidof(ICaptureGraphBuilder2), (LPVOID*)&m_pCaptureBuilder);
	hr = ::CoCreateInstance(CLSID_FilterGraph, 0, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&m_pGraphBuilder);
	hr = m_pCaptureBuilder->SetFiltergraph(m_pGraphBuilder);
	hr = m_pGraphBuilder->QueryInterface(IID_IMediaControl,(void**)&m_pMediaControl);
}

void	Engine::start() {
	if( m_bStarted ) {
		m_pMediaControl->Stop();
	}

	m_pMediaControl->Run();
	m_bStarted = true;
}

void	Engine::stop() {
	if( !m_bStarted )
		return;
	m_pMediaControl->Stop();
	m_bStarted = false;
}