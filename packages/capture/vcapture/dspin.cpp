#include "dspin.h"

DSPin::DSPin(IPin* pin)
: m_pPin(pin)
{
	if( m_pPin ) 
	{
		m_pPin->QueryPinInfo(&m_pinInfo);
	}
}

DSPin::~DSPin()
{

}

bool	DSPin::isInput()
{
	return m_pinInfo.dir == PINDIR_INPUT;
}

bool	DSPin::isOutput()
{
	return m_pinInfo.dir == PINDIR_OUTPUT;
}