#include "vcapfilefilter.h"
#include "vcapengine.h"
#include "vcapfilter.h"

VCapFileFilter::VCapFileFilter(VCapEngine* engine, const std::wstring& name)
: m_pEngine(engine)
, m_strName(name)
{
	IBaseFilter* ffilter = NULL;	
	m_pEngine->getCaptureBuilder()->SetOutputFileName(&MEDIASUBTYPE_Avi, name.c_str(), &ffilter, NULL);

	m_pFilter = new VCapFilter(ffilter);	
}

VCapFileFilter::~VCapFileFilter()
{
}

