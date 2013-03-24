#ifndef VCAPSPXENCFILTER_H
#define VCAPSPXENCFILTER_H

#include "vcapconfig.h"

class VCapFilter;
struct SpeexBits;
class VCapSpxEncFilter
{
public:
	VCapSpxEncFilter();
	~VCapSpxEncFilter();

public:
	void		init();
	VCapFilter*	filter() { return m_pFilter; }

private:
	VCapFilter*		m_pFilter;
};

#endif