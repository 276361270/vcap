#include "vcappin.h"

VCapPin::VCapPin(IPin* pin)
: m_pPin(pin)
{
	if( m_pPin ) 
	{
		m_pPin->QueryPinInfo(&m_pinInfo);
	}
}

VCapPin::~VCapPin()
{

}

bool	VCapPin::isInput()
{
	return m_pinInfo.dir == PINDIR_INPUT;
}

bool	VCapPin::isOutput()
{
	return m_pinInfo.dir == PINDIR_OUTPUT;
}