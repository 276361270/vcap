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

/*
void	VCapEngine::startCaptureAudio(const std::wstring& filename)
{
	if( !m_pAudioInputFilter || !m_pMediaControl )
		return;
	
	IBaseFilter* ffilter = NULL;
	m_pCaptureBuilder->SetOutputFileName(&MEDIASUBTYPE_Avi, filename.c_str(), &ffilter, NULL);
	m_pFileFilter = new VCapFilter(ffilter);
	m_pGraphBuilder->AddFilter(m_pFileFilter->filter(), L"file");

	m_pCaptureBuilder->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Audio, m_pAudioInputFilter->filter(), NULL, m_pFileFilter->filter());	
	m_pMediaControl->Run();
}

void	VCapEngine::stopCaptureAudio()
{
	m_pMediaControl->Stop();
}
*/
