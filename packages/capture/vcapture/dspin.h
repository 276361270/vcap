#ifndef DSPin_H
#define DSPin_H

#include "vcapconfig.h"

class DSPin
{
public:
	DSPin(IPin* pin);
	~DSPin();

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