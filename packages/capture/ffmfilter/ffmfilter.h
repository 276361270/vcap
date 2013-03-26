#ifndef FFMFILTER_H
#define FFMFILTER_H

#include "ffmconfig.h"

class FfmTransform;
class FfmFilter : public CTransformFilter
{
public:
	FfmFilter(LPUNKNOWN punk, HRESULT *phr);
	~FfmFilter();
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
	FfmTransform*	m_pTranform;
};

#endif