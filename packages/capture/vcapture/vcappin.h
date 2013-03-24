#ifndef VCAPPIN_H
#define VCAPPIN_H

#include "vcapconfig.h"

class VCapPin
{
public:
	VCapPin(IPin* pin);
	~VCapPin();

public:
	IPin*			pin() { return m_pPin; }
	std::wstring	getName();
	bool			isInput();
	bool			isOutput();

private:
	IPin*		m_pPin;
	PIN_INFO	m_pinInfo;
};

#endif