#include "ffmfilter.h"
#include "ffmtransform.h"
#include "ffmlog.h"
#include "ffmutil.h"

FfmFilter::FfmFilter(LPUNKNOWN punk, HRESULT *phr) 
: CTransformFilter(STR_FFMFILTER, punk, CLSID_FFMFILTER) 
{
	m_pTranform = new FfmTransform();
	m_nMediaType = 0;
	LOG_INIT();
}

FfmFilter::~FfmFilter()
{
}

CUnknown *FfmFilter::CreateInstance(LPUNKNOWN punk, HRESULT *phr)
{
    FfmFilter *pNewObject = new FfmFilter(punk, phr);

    if (pNewObject == NULL) {
        if (phr)
            *phr = E_OUTOFMEMORY;
    }
    return pNewObject;
}


STDMETHODIMP FfmFilter::NonDelegatingQueryInterface(REFIID riid, void **ppv)
{
    CheckPointer(ppv,E_POINTER);
    if (riid == IID_FFMFILTER) {
        *ppv = static_cast<IFfmFilter*>(this);
		return S_OK;

    } else {
        return CTransformFilter::NonDelegatingQueryInterface(riid, ppv);
    }

} 

HRESULT		FfmFilter::Transform(IMediaSample *pSource, IMediaSample *pDest)
{
    CheckPointer(pSource,E_POINTER);   
    CheckPointer(pDest,E_POINTER);   

	HRESULT hr = S_OK;
	int	time = 0;
	BYTE *pSourceBuffer, *pDestBuffer;
    long lSourceSize = pSource->GetActualDataLength();
    pSource->GetPointer(&pSourceBuffer);
    pDest->GetPointer(&pDestBuffer);
	long lDestSize = pDest->GetActualDataLength();

    // Copy the sample times
    REFERENCE_TIME TimeStart, TimeEnd;
	hr = pSource->GetTime(&TimeStart, &TimeEnd);
    if (NOERROR == hr) {
        //pDest->SetTime(&TimeStart, &TimeEnd);
		//time = TimeStart/10;	//100ns to ms
	} else if (VFW_E_SAMPLE_TIME_NOT_SET == hr ) {
		//FFMLOG("FfmFilter.Transform, GetTime returns ret=", hr);
	}

    LONGLONG MediaStart, MediaEnd;
    if (pSource->GetMediaTime(&MediaStart,&MediaEnd) == NOERROR) {
        pDest->SetMediaTime(&MediaStart,&MediaEnd);
    }

	//time is needed to calc the video pts/dts/during.
	if( m_pTranform ) 
	{
		if( time == 0 ) {
			//if the sample has no time stamp:
			time = FfmUtil::currentSystemTime();
		}
		//FFMLOG("FfmFilter.Transform, time/size=", time, lSourceSize);
		m_pTranform->onData(m_nMediaType, time, (char*)pSourceBuffer, lSourceSize, (char*)pDestBuffer, lDestSize);
	}

    // Copy the Sync point property
    hr = pSource->IsSyncPoint();
    if (hr == S_OK) {
        pDest->SetSyncPoint(TRUE);
    }
    else if (hr == S_FALSE) {
        pDest->SetSyncPoint(FALSE);
    }
    else {  // an unexpected error has occured...
        return E_UNEXPECTED;
    }

    // Copy the media type
    AM_MEDIA_TYPE *pMediaType;
    pSource->GetMediaType(&pMediaType);
    pDest->SetMediaType(pMediaType);
    DeleteMediaType(pMediaType);

    // Copy the preroll property
    hr = pSource->IsPreroll();
    if (hr == S_OK) {
        pDest->SetPreroll(TRUE);
    }
    else if (hr == S_FALSE) {
        pDest->SetPreroll(FALSE);
    }
    else {  // an unexpected error has occured...
        return E_UNEXPECTED;
    }

    // Copy the discontinuity property
    hr = pSource->IsDiscontinuity();
    if (hr == S_OK) {
    pDest->SetDiscontinuity(TRUE);
    }
    else if (hr == S_FALSE) {
        pDest->SetDiscontinuity(FALSE);
    }
    else {  // an unexpected error has occured...
        return E_UNEXPECTED;
    }

    // Copy the actual data length
    long lDataLength = pSource->GetActualDataLength();
    pDest->SetActualDataLength(lDataLength);

    return NOERROR;
}

HRESULT FfmFilter::CheckTransform(const CMediaType *mtIn, const CMediaType *mtOut)
{
	CheckPointer(mtIn,E_POINTER);
    CheckPointer(mtOut,E_POINTER);

    return NOERROR;
}

HRESULT FfmFilter::DecideBufferSize(IMemAllocator *pAlloc, ALLOCATOR_PROPERTIES *pProperties)
{
	if (m_pInput->IsConnected() == FALSE) {
        return E_UNEXPECTED;
    }

    CheckPointer(pAlloc,E_POINTER);
    CheckPointer(pProperties,E_POINTER);
    HRESULT hr = NOERROR;

    pProperties->cBuffers = 1;
    pProperties->cbBuffer = m_pInput->CurrentMediaType().GetSampleSize();
    ASSERT(pProperties->cbBuffer);

    // Ask the allocator to reserve us some sample memory, NOTE the function
    // can succeed (that is return NOERROR) but still not have allocated the
    // memory that we requested, so we must check we got whatever we wanted

    ALLOCATOR_PROPERTIES Actual;
    hr = pAlloc->SetProperties(pProperties,&Actual);
    if (FAILED(hr)) {
        return hr;
    }

    ASSERT( Actual.cBuffers == 1 );

    if (pProperties->cBuffers > Actual.cBuffers ||
            pProperties->cbBuffer > Actual.cbBuffer) {
                return E_FAIL;
    }
    return NOERROR;
}

HRESULT FfmFilter::CheckInputType(const CMediaType *mtIn)
{
    CheckPointer(mtIn,E_POINTER);    

    return S_OK;
}

HRESULT FfmFilter::GetMediaType(int iPosition, CMediaType *pMediaType)
{
	if (m_pInput->IsConnected() == FALSE) {
        return E_UNEXPECTED;
    }

    if (iPosition < 0) {
        return E_INVALIDARG;
    }    

    if (iPosition > 0) {
        return VFW_S_NO_MORE_ITEMS;
    }

    CheckPointer(pMediaType,E_POINTER);
    *pMediaType = m_pInput->CurrentMediaType();

    return NOERROR;
}

void	FfmFilter::setServerIp(char* ip, int port, char* app, char* stream)
{
	m_strIp = ip;
	m_nPort = port;
	m_strApp = app;
	m_strStream = stream;
}

void	FfmFilter::setMediaType(int type)
{
	m_nMediaType = type;
	m_pTranform->setup(type, const_cast<char*>(m_strIp.c_str()), m_nPort, const_cast<char*>(m_strApp.c_str()), const_cast<char*>(m_strStream.c_str()));
}

void	FfmFilter::setVideoSize(int width, int height)
{
	m_pTranform->setVideoSize(width, height);
}