#ifndef VCAPAUDIOENCODEFACTORY_H
#define VCAPAUDIOENCODEFACTORY_H

#include "vcapconfig.h"

class VCapAudioEncoder;
class VCapAudioEncoderFactory
{
public:
	static 	std::vector<VCapAudioEncoder*>	enumFilters();
	static VCapAudioEncoder*		findFilter(const std::wstring& name);

};

#endif