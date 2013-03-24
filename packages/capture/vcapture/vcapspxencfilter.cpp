#include "vcapspxencfilter.h"
#include "vcapfilter.h"

VCapSpxEncFilter::VCapSpxEncFilter()
{
	m_pFilter = NULL;
	init();
}

VCapSpxEncFilter::~VCapSpxEncFilter()
{
}

void	VCapSpxEncFilter::init()
{
	HRESULT hr = S_OK;
	IBaseFilter* filter = NULL;

	hr = ::CoCreateInstance(CLSID_SPXFILTER, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&filter);
	if( FAILED(hr) )
		return;
	m_pFilter = new VCapFilter(filter);
}