#ifndef VCAPFILTER_H
#define VCAPFILTER_H

#include "vcapconfig.h"
#include <vector>

class VCapPin;
class VCapEngine;
class VCapFilter
{
public:
	VCapFilter(IBaseFilter* filter);
	VCapFilter(IMoniker* moniker);
	~VCapFilter();

public:
	void		enumPins();
	VCapPin*	getOutputPin();

public:
	IBaseFilter*	filter() { return m_pBaseFilter; }
	std::wstring	name() { return m_wstrName; }
	

private:
	IBaseFilter*	m_pBaseFilter;
	std::wstring	m_wstrName;
	std::vector<VCapPin*>	m_arrPins;
};

#endif