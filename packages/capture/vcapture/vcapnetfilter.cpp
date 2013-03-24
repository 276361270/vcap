#include "vcapnetfilter.h"
#include "vcapfilter.h"

VCapNetFilter::VCapNetFilter()
{
	init();
}

VCapNetFilter::~VCapNetFilter()
{
}


void	VCapNetFilter::onData(void* data, int len)
{

}

void	VCapNetFilter::init() 
{
	HRESULT hr = S_OK;
	IBaseFilter* filter = NULL;

	hr = ::CoCreateInstance(CLSID_DSRFILTER, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&filter);
	if( FAILED(hr) )
		return;
	m_pFilter = new VCapFilter(filter);

	IDsrFilter*	pDsNet = NULL;
	filter->QueryInterface(IID_DSRFILTER, (void**)&pDsNet);
	pDsNet->setCallback(this);
}