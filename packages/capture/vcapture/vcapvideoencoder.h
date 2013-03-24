#ifndef VCAPVIDEOENCODER_H
#define VCAPVIDEOENCODER_H

#include "vcapconfig.h"

class VCapFilter;
class VCapPin;
class VCapVideoEncoder
{
public:
	VCapVideoEncoder(VCapFilter* filter);
	~VCapVideoEncoder();

public:
	void	enumCaps();

public:
	VCapFilter*	filter() { return m_pFilter; }

private:
	VCapFilter*			m_pFilter;
	VCapPin*			m_pOutPin;
	IAMStreamConfig*	m_pStreamConfig;
};

#endif