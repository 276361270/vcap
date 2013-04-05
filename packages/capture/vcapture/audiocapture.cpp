#include "audiocapture.h"
#include "engine.h"
#include "mic.h"
#include "micfactory.h"
#include "filefilter.h"
#include "dsfilter.h"
#include "ffmencoder.h"

AudioCapture::AudioCapture()
{	
	m_pEngine = NULL;
	m_pFfmEncoder = NULL;
	m_pFileFilter = NULL;
	m_pMic = NULL;
}

AudioCapture::~AudioCapture()
{
	if( m_pEngine )
		delete m_pEngine;
	if( m_pFfmEncoder ) 
		delete m_pFfmEncoder;
	if( m_pFileFilter )
		delete m_pFileFilter;
	if( m_pMic )
		delete m_pMic;
}

void	AudioCapture::setFileName(const wchar_t* filename)
{
	m_wstrFileName.assign(filename);
}

int		AudioCapture::startCapture()
{
	HRESULT hr = S_OK;

	m_arrMics = MicFactory::enumMics();
	if( m_arrMics.size() > 0 ) {
		m_pMic = m_arrMics[0];
	} else {
		return VCAP_ERROR_NO_MIC;
	}

	m_pEngine = new Engine();
	m_pFfmEncoder = new FfmEncoder();
	m_pFfmEncoder->setup(FFM_MEDIA_AUDIO, "127.0.0.1", 8080, "live", "live2");

	if( m_wstrFileName.size() > 0 ) {
		m_pFileFilter = new FileFilter(m_pEngine, m_wstrFileName.c_str());	
	}

	m_pEngine->getGraphBuilder()->AddFilter( m_pMic->filter()->filter(), L"Microphone");
	m_pEngine->getGraphBuilder()->AddFilter( m_pFfmEncoder->filter()->filter(), L"Ffm Encoder");
	if( m_pFileFilter ) {
		m_pEngine->getGraphBuilder()->AddFilter( m_pFileFilter->filter()->filter(), L"File Writer");	
	}
	
	if( m_pFileFilter ) {
		hr = m_pEngine->getCaptureBuilder()->RenderStream(&PIN_CATEGORY_CAPTURE, 
			&MEDIATYPE_Audio, 
			m_pMic->filter()->filter(), 
			m_pFfmEncoder->filter()->filter(),
			m_pFileFilter->filter()->filter());
	} else {
		hr = m_pEngine->getCaptureBuilder()->RenderStream(&PIN_CATEGORY_CAPTURE, 
			&MEDIATYPE_Audio, 
			m_pMic->filter()->filter(), 
			m_pFfmEncoder->filter()->filter(),
			NULL);
	}
	m_pEngine->start();

	return VCAP_ERROR_OK;
}

int		AudioCapture::stopCapture()
{
	m_pEngine->stop();
	return VCAP_ERROR_OK;
}