#include "vcapspxencfilter.h"
#include "vcapfilter.h"

VCapSpxEncFilter::VCapSpxEncFilter()
{
	m_pFilter = NULL;
	init();
	m_pSpxState = speex_encoder_init(&speex_nb_mode);
	speex_bits_init(&m_spxBits);

	speex_encoder_ctl(m_pSpxState, SPEEX_MODE_FRAME_SIZE, &m_nFrameSize);
}

VCapSpxEncFilter::~VCapSpxEncFilter()
{
}

void	VCapSpxEncFilter::onData(IMediaSample* pSource, IMediaSample* pDest)
{
	BYTE *pSourceBuffer, *pDestBuffer;
    long lSourceSize = pSource->GetActualDataLength();
	long nDestSize = pDest->GetSize();

#ifdef DEBUG
    long lDestSize = pDest->GetSize();
    ASSERT(lDestSize >= lSourceSize);
#endif

    pSource->GetPointer(&pSourceBuffer);
    pDest->GetPointer(&pDestBuffer);

    //CopyMemory( (PVOID) pDestBuffer,(PVOID) pSourceBuffer,lSourceSize);
	speex_bits_reset(&m_spxBits);
	speex_encode_int(m_pSpxState, (spx_int16_t*)pSourceBuffer, &m_spxBits);
	speex_bits_write(&m_spxBits, (char*)pDestBuffer, nDestSize);

    // Copy the sample times

    REFERENCE_TIME TimeStart, TimeEnd;
    if (NOERROR == pSource->GetTime(&TimeStart, &TimeEnd)) {
        pDest->SetTime(&TimeStart, &TimeEnd);
    }

    LONGLONG MediaStart, MediaEnd;
    if (pSource->GetMediaTime(&MediaStart,&MediaEnd) == NOERROR) {
        pDest->SetMediaTime(&MediaStart,&MediaEnd);
    }

    // Copy the Sync point property

    HRESULT hr = pSource->IsSyncPoint();
    if (hr == S_OK) {
        pDest->SetSyncPoint(TRUE);
    }
    else if (hr == S_FALSE) {
        pDest->SetSyncPoint(FALSE);
    }
    else {  // an unexpected error has occured...
        return;
    }

    // Copy the media type

    AM_MEDIA_TYPE *pMediaType;
    pSource->GetMediaType(&pMediaType);
    pDest->SetMediaType(pMediaType);
    //DeleteMediaType(pMediaType);

    // Copy the preroll property

    hr = pSource->IsPreroll();
    if (hr == S_OK) {
        pDest->SetPreroll(TRUE);
    }
    else if (hr == S_FALSE) {
        pDest->SetPreroll(FALSE);
    }
    else {  // an unexpected error has occured...
        return;
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
        return;
    }

    // Copy the actual data length

    long lDataLength = pSource->GetActualDataLength();
    pDest->SetActualDataLength(lDataLength);
}

void	VCapSpxEncFilter::init()
{
	HRESULT hr = S_OK;
	IBaseFilter* filter = NULL;

	hr = ::CoCreateInstance(CLSID_DSXFILTER, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&filter);
	if( FAILED(hr) )
		return;
	m_pFilter = new VCapFilter(filter);

	IDsxFilter*	dsx = NULL;
	filter->QueryInterface(IID_DSXFILTER, (void**)&dsx);
	dsx->setCallback(this);
}