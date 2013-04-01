#ifndef FileFilter_H
#define FileFilter_H

#include "vcapconfig.h"

class Engine;
class DSFilter;
class FileFilter
{
public:
	FileFilter(Engine* engine, const std::wstring& name);
	~FileFilter();

public:
	DSFilter*		filter() { return m_pFilter; }

private:
	Engine*		m_pEngine;
	DSFilter*		m_pFilter;
	std::wstring	m_strName;
};


#endif