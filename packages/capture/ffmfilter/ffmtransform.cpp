#include "ffmtransform.h"
#include "ffmaachandler.h"
#include "ffmh264handler.h"
#include "ffmlog.h"

FfmTransform::FfmTransform()
{	
	::av_register_all();
	m_pAacHandler = new FfmAacHandler();
	m_pH264Handler = new FfmH264Handler();
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

void	FfmTransform::open() {
	if( m_pAacHandler ) {
		m_pAacHandler->open();
	}
	if( m_pH264Handler ) {
		m_pH264Handler->open();
	}
}

int		FfmTransform::onData(int media_type, char* src, int inlen, char* dest, int outlen) {
	switch(media_type) {
		case FFM_MEDIA_AUDIO:
			return m_pAacHandler->onData(src, inlen, dest, outlen);
			break;
		case FFM_MEDIA_VIDEO:
			if( m_pH264Handler ) {
			return m_pH264Handler->onData(src, inlen, dest, outlen);
			}
			break;
	}
}

void	FfmTransform::close() {
	if( m_pAacHandler ) {
		m_pAacHandler->close();
	}
	if( m_pH264Handler ) {
		m_pH264Handler->close();
	}
}