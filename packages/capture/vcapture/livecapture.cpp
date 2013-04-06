#include "livecapture.h"
#include "engine.h"
#include "camera.h"
#include "videocapture.h"
#include "audiocapture.h"

LiveCapture::LiveCapture()
{
	m_pVideoCapture = new VideoCapture();
	m_pAudioCapture = new AudioCapture();
}

LiveCapture::~LiveCapture()
{
	if( m_pVideoCapture )
		delete m_pVideoCapture;
	if( m_pAudioCapture )
		delete m_pAudioCapture;
}

void	LiveCapture::setAudioServer(char* ip, int port, char* app, char* stream)
{

}

void	LiveCapture::setVideoServer(char* ip, int port, char* app, char* stream)
{

}

int		LiveCapture::startCapture(int hWnd)
{	
	m_pVideoCapture->startCapture(hWnd);
	m_pAudioCapture->startCapture();

	return 0;
}

int		LiveCapture::stopCapture()
{
	m_pVideoCapture->stopCapture();
	m_pAudioCapture->stopCapture();
	return 0;
}

void	LiveCapture::paint()
{
	if( m_pVideoCapture ) {
		m_pVideoCapture->paint();
	}
}
