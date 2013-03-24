#ifndef DSXFILTER_H
#define DSXFILTER_H

#include "dsxconfig.h"

class X264Transform;
class DsxFilter : public CTransformFilter
{
public:
	DsxFilter(LPUNKNOWN punk, HRESULT *phr);
	~DsxFilter();
	DECLARE_IUNKNOWN;

public:    
    static CUnknown * WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);

    STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void ** ppv);

    HRESULT Transform(IMediaSample *pIn, IMediaSample *pOut);
    HRESULT CheckInputType(const CMediaType *mtIn);
    HRESULT CheckTransform(const CMediaType *mtIn, const CMediaType *mtOut);
    HRESULT DecideBufferSize(IMemAllocator *pAlloc,
                             ALLOCATOR_PROPERTIES *pProperties);
    HRESULT GetMediaType(int iPosition, CMediaType *pMediaType);

private:
    CCritSec    m_EZrgb24Lock;
    CRefTime    m_effectStartTime;
    CRefTime    m_effectTime;
	X264Transform*	m_pX264;
};

#endif