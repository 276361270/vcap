#ifndef VCAPNETFILTER_H
#define VCAPNETFILTER_H

#include "vcapconfig.h"

class VCapFilter;
class VCapNetFilter : public IDsrCallback
{
public:
	VCapNetFilter();
	~VCapNetFilter();

public:
	virtual void	onData(void* data, int len);

public:
	void		init();
	VCapFilter*	filter() { return m_pFilter; }

private:
	VCapFilter*		m_pFilter;
};


#endif