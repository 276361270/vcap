#include "livecapture.h"
#include "engine.h"
#include "camera.h"
#include "videocapture.h"
#include "audiocapture.h"
#include "enginefactory.h"

LiveCapture::LiveCapture()
{
	m_pEngine = EngineFactory::getInstance();
	m_pVideoCapture = new VideoCapture(m_pEngine);
	m_pAudioCapture = new AudioCapture(m_pEngine);
}

LiveCapture::~LiveCapture()
{
	if( m_pVideoCapture )
		delete m_pVideoCapture;
	if( m_pAudioCapture )
		delete m_pAudioCapture;
	if( m_pEngine ) 
		delete m_pEngine;
}

int		LiveCapture::startCapture(int hWnd)
{	
	m_pVideoCapture->startCapture(hWnd);
	m_pAudioCapture->startCapture();

	return 0;
}

int		LiveCapture::stopCapture()
{
	m_pEngine->stop();
	return 0;
}

void	LiveCapture::paint()
{
	if( m_pVideoCapture ) {
		m_pVideoCapture->paint();
	}
}
