#include "mic.h"
#include "dsfilter.h"
#include "dspin.h"

Mic::Mic(DSFilter* filter)
: m_pFilter(filter)
{	
	HRESULT hr = S_OK;

	hr = m_pFilter->getOutputPin()->pin()->QueryInterface(IID_IAMStreamConfig, (void**)&m_pConfig);
	if( m_pConfig == NULL )
		return;

	hr = m_pConfig->GetFormat(&m_pFormat);
	if( m_pFormat->formattype == FORMAT_WaveFormatEx )
	{
		m_pWaveInfo = (WAVEFORMATEX*)m_pFormat->pbFormat;
	}

	memset(&m_bufprops, 0, sizeof(m_bufprops));
	hr = m_pFilter->getOutputPin()->pin()->QueryInterface(IID_IAMBufferNegotiation, (void**)&m_pBuffCtl);
	//hr = m_pBuffCtl->GetAllocatorProperties(&m_bufprops);
	m_bufprops.cBuffers = 6;
	m_bufprops.cbBuffer = 1024*4;
	m_bufprops.cbAlign = 2;
	m_bufprops.cbPrefix = 0;
	hr = m_pBuffCtl->SuggestAllocatorProperties(&m_bufprops);
}

Mic::~Mic()
{
}