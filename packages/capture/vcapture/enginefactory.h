#ifndef EngineFactory_H
#define EngineFactory_H

#include "vcapconfig.h"

class Engine;
class EngineFactory
{
public:
	static Engine*		getInstance();

};


#endif