#ifndef FFMENCODER_H
#define FFMENCODER_H

#include "vcapconfig.h"

class VCapFilter;
class FfmEncoder
{
public:
	FfmEncoder(int media_type);
	~FfmEncoder();

public:	
	VCapFilter*	filter() { return m_pFilter; }

private:
	void		init();

private:
	VCapFilter*		m_pFilter;
	IFfmFilter*		m_pFfmFilter;
	int				m_nMediaType;
};

#endif