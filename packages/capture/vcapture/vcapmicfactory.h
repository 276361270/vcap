#ifndef VCAPMICFACTORY_H
#define VCAPMICFACTORY_H

#include "vcapconfig.h"

class VCapMic;
class VCapMicFactory
{
public:
	static std::vector<VCapMic*>		enumMics();

};

#endif