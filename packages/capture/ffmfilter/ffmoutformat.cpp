#include "ffmoutformat.h"
#include "ffmlog.h"

FfmOutFormat::FfmOutFormat()
{	
	m_bOpened = false;
	m_bConnected = false;
}

FfmOutFormat::~FfmOutFormat()
{
}

void	FfmOutFormat::init(char* fmt, char* url)
{
	m_strFmt = fmt;
	m_strUrl = url;
	int ret = ::avformat_alloc_output_context2(&m_pFormatContext, NULL, fmt, url);
	if( ret < 0 ) {
		FFMLOG("FfmOutFormat::init, ret=", ret);
	}
}

void	FfmOutFormat::connectServer()
{
	int ret = 0;
	if( m_bOpened ) {
		FFMLOG("FfmOutFormat::connect, already opened.");
		return;
	}

	ret = ::avio_open(&m_pFormatContext->pb, m_strUrl.c_str(), AVIO_FLAG_WRITE);
	if( ret != 0 ) {
		FFMLOG("FfmH264Handler::connect, avio_open failed ret=", ret);
		return;
	}
	m_bOpened = true;
	ret = ::avformat_write_header(m_pFormatContext, NULL);
	if( ret < 0 ) {
		FFMLOG("FfmH264Handler::connect, avformat_write_header failed ret=", ret);
		return;
	}
}

void	FfmOutFormat::close()
{	
	if( m_pFormatContext ) {
		::av_write_trailer(m_pFormatContext);
		avio_close(m_pFormatContext->pb);
		avformat_free_context(m_pFormatContext);
		m_pFormatContext = NULL;
	}	

	m_bOpened = false;
}