#include "ffmoutformat.h"
#include "ffmlog.h"

FfmOutFormat::FfmOutFormat(char* ip, short port)
{
	m_pstrUrl = new char[MAX_PATH];
	memset(m_pstrUrl, 0, MAX_PATH);
	sprintf(m_pstrUrl, "udp://%s:%d", ip, port);
	int ret = ::avformat_alloc_output_context2(&m_pFormatContext, NULL, "mpegts", m_pstrUrl);

}

FfmOutFormat::~FfmOutFormat()
{

}

void	FfmOutFormat::open()
{
	int ret = ::avio_open(&m_pFormatContext->pb, m_pstrUrl, AVIO_FLAG_WRITE);
	if( ret != 0 ) {
		FFMLOG("FfmH264Handler::open, avio_open failed ret=", ret);
		return;
	}
	::avformat_write_header(m_pFormatContext, NULL);
}

void	FfmOutFormat::close()
{	
	if( m_pFormatContext ) {
		::av_write_trailer(m_pFormatContext);
		avio_close(m_pFormatContext->pb);
		avformat_free_context(m_pFormatContext);
		m_pFormatContext = NULL;
	}	
}