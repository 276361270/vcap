#include "vcapvideoencoder.h"
#include "vcapfilter.h"
#include "vcappin.h"

VCapVideoEncoder::VCapVideoEncoder(VCapFilter* filter)
: m_pFilter(filter)
{
	m_pOutPin = m_pFilter->getOutputPin();
	if( !m_pOutPin )
		return;	
	m_pOutPin->pin()->QueryInterface(IID_IAMStreamConfig , (void**)&m_pStreamConfig);

	enumCaps();
}

VCapVideoEncoder::~VCapVideoEncoder()
{	
	m_pStreamConfig->Release();
}

void	VCapVideoEncoder::enumCaps()
{
	if( !m_pStreamConfig )
		return;

	int count=0, size=0;
	char* buf = NULL;
	m_pStreamConfig->GetNumberOfCapabilities(&count, &size);
	buf = new char[size];
	AM_MEDIA_TYPE*	media;

	for( int i=0; i<count; i++ )
	{		
		m_pStreamConfig->GetStreamCaps(i, &media, (BYTE*)buf);		
	}
	delete[] buf;
}