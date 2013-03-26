#include "vcapmic.h"
#include "vcapfilter.h"
#include "vcappin.h"

VCapMic::VCapMic(VCapFilter* filter)
: m_pFilter(filter)
{	
	m_pFilter->getOutputPin()->pin()->QueryInterface(IID_IAMStreamConfig, (void**)&m_pConfig);
	if( m_pConfig == NULL )
		return;

	m_pConfig->GetFormat(&m_pFormat);
	if( m_pFormat->formattype == FORMAT_WaveFormatEx )
	{
		m_pWaveInfo = (WAVEFORMATEX*)m_pFormat->pbFormat;
	}
}

VCapMic::~VCapMic()
{
}