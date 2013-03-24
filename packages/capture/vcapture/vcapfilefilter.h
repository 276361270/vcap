#ifndef VCAPFILEFILTER_H
#define VCAPFILEFILTER_H

#include "vcapconfig.h"

class VCapEngine;
class VCapFilter;
class VCapFileFilter
{
public:
	VCapFileFilter(VCapEngine* engine, const std::wstring& name);
	~VCapFileFilter();

public:
	VCapFilter*		filter() { return m_pFilter; }

private:
	VCapEngine*		m_pEngine;
	VCapFilter*		m_pFilter;
	std::wstring	m_strName;
};


#endif