#include "ffmencoder.h"
#include "dsfilter.h"

FfmEncoder::FfmEncoder(int media_type)
: m_nMediaType(media_type)
{
	m_pFilter = NULL;
	m_pFfmFilter = NULL;
	init();
}

FfmEncoder::~FfmEncoder()
{
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
	m_pFfmFilter->setMediaType(m_nMediaType);
}