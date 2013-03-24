#ifndef VCAPVIDEOENCODER_H
#define VCAPVIDEOENCODER_H

#include "vcapconfig.h"

class VCapFilter;
class VCapAudioEncoder
{
public:
	VCapAudioEncoder(VCapFilter* filter);
	~VCapAudioEncoder();

public:
	VCapFilter*		filter() { return m_pFilter; }

private:
	VCapFilter*		m_pFilter;
};

#endif