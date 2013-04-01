#ifndef DSFilter_H
#define DSFilter_H

#include "vcapconfig.h"
#include <vector>

class DSPin;
class Engine;
class DSFilter
{
public:
	DSFilter(IBaseFilter* filter);
	DSFilter(IMoniker* moniker);
	~DSFilter();

public:
	void		enumPins();
	DSPin*	getOutputPin();

public:
	IBaseFilter*	filter() { return m_pBaseFilter; }
	std::wstring	name() { return m_wstrName; }
	

private:
	IBaseFilter*	m_pBaseFilter;
	std::wstring	m_wstrName;
	std::vector<DSPin*>	m_arrPins;
};

#endif