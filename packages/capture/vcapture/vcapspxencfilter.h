#ifndef VCAPSPXENCFILTER_H
#define VCAPSPXENCFILTER_H

#include "vcapconfig.h"

class VCapFilter;
struct SpeexBits;
class VCapSpxEncFilter : public IDsxCallback
{
public:
	VCapSpxEncFilter();
	~VCapSpxEncFilter();

public:
	virtual void	onData(IMediaSample* src, IMediaSample* dest);

public:
	void		init();
	VCapFilter*	filter() { return m_pFilter; }

private:
	VCapFilter*		m_pFilter;
	void*			m_pSpxState;
	SpeexBits		m_spxBits;
	int				m_nFrameSize;
};

#endif