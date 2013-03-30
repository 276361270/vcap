#include "ffmtransform.h"
#include "ffmaachandler.h"
#include "ffmh264handler.h"
#include "ffmlog.h"

static void log_callback(void* ptr, int level,const char* fmt,va_list vl);
FfmTransform::FfmTransform()
{	
	::av_register_all();
	m_pAacHandler = new FfmAacHandler();
	m_pH264Handler = new FfmH264Handler();

	::av_log_set_callback(log_callback);
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

int		FfmTransform::onData(int media_type, LONGLONG time,  char* src, int inlen, char* dest, int outlen) {
	switch(media_type) {
		case FFM_MEDIA_AUDIO:
			return m_pAacHandler->onData(time, src, inlen, dest, outlen);
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
	}
	if( m_pH264Handler ) {
		m_pH264Handler->close();
	}
}

static void log_callback(void* ptr, int level,const char* fmt,va_list vl)  
{
	/*
	static FILE *fp = NULL;     

	if(!fp)     
		fp = fopen("d:\\ffmpeg.log","a+");     
	if(fp)  
	{     
		vfprintf(fp,fmt,vl);     
		fflush(fp);   
		fclose(fp);  
	}  
	*/
	printf(fmt, vl);
}