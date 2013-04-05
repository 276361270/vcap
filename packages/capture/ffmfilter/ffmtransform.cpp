#include "ffmtransform.h"
#include "ffmoutformat.h"
#include "ffmaachandler.h"
#include "ffmh264handler.h"
#include "ffmlog.h"

FfmTransform::FfmTransform()
{	
	::av_register_all();
	avformat_network_init();
	
	m_pAacHandler = NULL;
	m_pH264Handler = NULL;
}

FfmTransform::~FfmTransform()
{	
	if( m_pAacHandler ) {
		delete m_pAacHandler;
		m_pAacHandler = NULL;
	}
	if( m_pH264Handler ) {
		delete m_pH264Handler;
		m_pH264Handler = NULL;
	}
}

void	FfmTransform::setup(int media_type, char* ip, int port, char* app, char* stream) {
	if( media_type == FFM_MEDIA_AUDIO ) {
		m_pAacHandler = new FfmAacHandler();
		m_pAacHandler->setup(ip, port, app, stream);
	
	} else if( media_type == FFM_MEDIA_VIDEO) {
		m_pH264Handler = new FfmH264Handler();
		m_pH264Handler->setup(ip, port, app, stream);
	}
}

int		FfmTransform::onData(int media_type, LONGLONG time,  char* src, int inlen, char* dest, int outlen) {
	switch(media_type) {
		case FFM_MEDIA_AUDIO:
			if( m_pAacHandler ) {
				return m_pAacHandler->onData(time, src, inlen, dest, outlen);
			}
			break;
		case FFM_MEDIA_VIDEO:
			if( m_pH264Handler ) {
				return m_pH264Handler->onData(time, src, inlen, dest, outlen);
			}
			break;
	}

	return 0;
}

void	FfmTransform::close() {
	if( m_pAacHandler ) {
		m_pAacHandler->close();
		m_pAacHandler = NULL;
	}
	if( m_pH264Handler ) {
		m_pH264Handler->close();
		m_pH264Handler = NULL;
	}
}

void	FfmTransform::setVideoSize(int width, int height)
{
	if( m_pH264Handler ) {
		m_pH264Handler->setVideoSize(width, height);
	}
}