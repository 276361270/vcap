#ifndef Mic_H
#define Mic_H

#include "vcapconfig.h"

class DSFilter;
class Mic
{
public:
	struct Property
	{
		long	min;
		long	max;
		long	step;
		long	def;
		long	flags;
	};

public:
	Mic(DSFilter* filter);
	~Mic();

public:
	DSFilter*		filter() { return m_pFilter; }

private:
	DSFilter*		m_pFilter;
	IAMStreamConfig*m_pConfig;
	AM_MEDIA_TYPE*	m_pFormat;
	WAVEFORMATEX*	m_pWaveInfo;
	IAMBufferNegotiation*	m_pBuffCtl;
	ALLOCATOR_PROPERTIES	m_bufprops;
};

#endif