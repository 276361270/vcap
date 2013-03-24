#ifndef VCAPVIDEOENCODEFACTORY_H
#define VCAPVIDEOENCODEFACTORY_H

#include "vcapconfig.h"

class VCapVideoEncoder;
class VCapVideoEncoderFactory
{
public:
	static 	std::vector<VCapVideoEncoder*>	enumFilters();
	static VCapVideoEncoder*		findFilter(const std::wstring& name);

};

#endif