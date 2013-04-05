#include "ffmencoder.h"
#include "dsfilter.h"

FfmEncoder::FfmEncoder()
{
	m_pFilter = NULL;
	m_pFfmFilter = NULL;
	init();
}

FfmEncoder::~FfmEncoder()
{
}

void	FfmEncoder::setup(int media_type, char* ip, int port, char* app, char* stream)
{
	m_pFfmFilter->setServerIp(ip, port, app, stream);
	m_pFfmFilter->setMediaType(media_type);
}

void	FfmEncoder::init()
{
	HRESULT hr = S_OK;
	IBaseFilter* filter = NULL;

	hr = ::CoCreateInstance(CLSID_FFMFILTER, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&filter);
	if( FAILED(hr) )
		return;
	m_pFilter = new DSFilter(filter);
	filter->QueryInterface(IID_FFMFILTER, (void**)&m_pFfmFilter);
	
	
}