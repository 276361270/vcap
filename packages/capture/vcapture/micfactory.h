#ifndef MicFactory_H
#define MicFactory_H

#include "vcapconfig.h"

class Mic;
class MicFactory
{
public:
	static std::vector<Mic*>		enumMics();

};

#endif