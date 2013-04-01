#include "enginefactory.h"
#include "engine.h"

static Engine*	s_pEngineInstance = NULL;

Engine*		EngineFactory::getInstance()
{
	if( !s_pEngineInstance )
		s_pEngineInstance = new Engine();

	return s_pEngineInstance;
}

