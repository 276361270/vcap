#include "filefilter.h"
#include "engine.h"
#include "dsfilter.h"

FileFilter::FileFilter(Engine* engine, const std::wstring& name)
: m_pEngine(engine)
, m_strName(name)
{
	IBaseFilter* ffilter = NULL;	
	m_pEngine->getCaptureBuilder()->SetOutputFileName(&MEDIASUBTYPE_Avi, name.c_str(), &ffilter, NULL);

	m_pFilter = new DSFilter(ffilter);	
}

FileFilter::~FileFilter()
{
}

