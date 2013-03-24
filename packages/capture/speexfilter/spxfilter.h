#ifndef SPXFILTER_H
#define SPXFILTER_H

#include "spxconfig.h"

class SpxTransform;
class SpxFilter : public CTransformFilter
{
public:
	SpxFilter(LPUNKNOWN punk, HRESULT *phr);
	~SpxFilter();
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
	SpxTransform*	m_pSpeex;
};

#endif