#include "vcapmicfactory.h"
#include "vcapfilter.h"
#include "vcapmic.h"

std::vector<VCapMic*>	VCapMicFactory::enumMics()
{
	std::vector<VCapMic*> mics;

	ICreateDevEnum*	pSysDevEnum=NULL;
	IEnumMoniker *	pEnumCat=NULL;
	IMoniker *		pMoniker=NULL;
	HRESULT			hr = S_OK;

	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void **)&pSysDevEnum);
	if( !pSysDevEnum || FAILED(hr) )
		return mics;

	hr = pSysDevEnum->CreateClassEnumerator(CLSID_AudioInputDeviceCategory, &pEnumCat, 0);
	if( !pEnumCat || FAILED(hr) )
		return mics;

	ULONG cFetched;
	while(pEnumCat->Next(1, &pMoniker, &cFetched) == S_OK)
	{
		VCapFilter*	filter = new VCapFilter(pMoniker);
		mics.push_back( new VCapMic(filter) );
	}

	return mics;
}