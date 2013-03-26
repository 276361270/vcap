#ifndef FFMENCODER_H
#define FFMENCODER_H

#include "vcapconfig.h"

class VCapFilter;
class FfmEncoder
{
public:
	FfmEncoder();
	~FfmEncoder();

public:
	void		init();
	VCapFilter*	filter() { return m_pFilter; }

private:
	VCapFilter*		m_pFilter;
};

#endif