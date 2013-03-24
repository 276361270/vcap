#ifndef VCAPMIC_H
#define VCAPMIC_H

#include "vcapconfig.h"

class VCapFilter;
class VCapMic
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
	VCapMic(VCapFilter* filter);
	~VCapMic();

public:
	VCapFilter*		filter() { return m_pFilter; }

private:
	VCapFilter*		m_pFilter;
};

#endif