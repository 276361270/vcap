#include "ffmencoder.h"
#include "vcapfilter.h"

FfmEncoder::FfmEncoder()
{
	m_pFilter = NULL;
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
	m_pFilter = new VCapFilter(filter);
}