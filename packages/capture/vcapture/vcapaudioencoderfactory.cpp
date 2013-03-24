#include "vcapaudioencoderfactory.h"
#include "vcapaudioencoder.h"
#include "vcapfilter.h"

std::vector<VCapAudioEncoder*>	VCapAudioEncoderFactory::enumFilters()
{
	std::vector<VCapAudioEncoder*>	encoders;
	ICreateDevEnum*	pSysDevEnum=NULL;
	IEnumMoniker *	pEnumCat=NULL;
	IMoniker *		pMoniker=NULL;

	CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void **)&pSysDevEnum);
	pSysDevEnum->CreateClassEnumerator(CLSID_VideoCompressorCategory, &pEnumCat, 0);

	ULONG cFetched;
	while(pEnumCat->Next(1, &pMoniker, &cFetched) == S_OK)
	{
		VCapFilter*	filter = new VCapFilter(pMoniker);
		encoders.push_back( new VCapAudioEncoder(filter) );	
	}
	return encoders;
}

VCapAudioEncoder*	VCapAudioEncoderFactory::findFilter(const std::wstring& name)
{
	ICreateDevEnum*	pSysDevEnum=NULL;
	IEnumMoniker *	pEnumCat=NULL;
	IMoniker *		pMoniker=NULL;

	CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void **)&pSysDevEnum);
	pSysDevEnum->CreateClassEnumerator(CLSID_VideoCompressorCategory, &pEnumCat, 0);

	ULONG cFetched;
	while(pEnumCat->Next(1, &pMoniker, &cFetched) == S_OK)
	{
		VCapFilter*	filter = new VCapFilter(pMoniker);
		if( filter->name().find( name ) != -1 )
			return new VCapAudioEncoder(filter);
	}

	return NULL;
}

