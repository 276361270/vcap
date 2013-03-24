#ifndef VCAPSAMPLEGRABBER_H
#define VCAPSAMPLEGRABBER_H

#include "vcapconfig.h"

class VCapSampleGrabber
{
public:
	VCapSampleGrabber();
	~VCapSampleGrabber();

public:
	void	init();

private:
	IBaseFilter*		m_pFilter;
	ISampleGrabber*		m_pGrabber;
};

#endif