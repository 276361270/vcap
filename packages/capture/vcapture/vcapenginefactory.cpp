#include "vcapenginefactory.h"
#include "vcapengine.h"

static VCapEngine*	s_pEngineInstance = NULL;

VCapEngine*		VCapEngineFactory::getInstance()
{
	if( !s_pEngineInstance )
		s_pEngineInstance = new VCapEngine();

	return s_pEngineInstance;
}

