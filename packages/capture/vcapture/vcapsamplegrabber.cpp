#include "vcapsamplegrabber.h"

VCapSampleGrabber::VCapSampleGrabber()
{
}

VCapSampleGrabber::~VCapSampleGrabber()
{
}

void	VCapSampleGrabber::init() 
{
	HRESULT hr = S_OK;
	hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&m_pFilter);
	if( FAILED(hr) )
	{
		return;
	}

	hr = m_pFilter->QueryInterface( IID_ISampleGrabber, (void**)&m_pGrabber);
	if( FAILED(hr) )
	{
		return;
	}

	AM_MEDIA_TYPE mt;
    ZeroMemory(&mt, sizeof(mt));
    mt.majortype = MEDIATYPE_Video;
    mt.subtype = MEDIASUBTYPE_RGB24;

    hr = m_pGrabber->SetMediaType(&mt);
    if (FAILED(hr))
    {
		return; //[yunzed] leaks here.
    }
}