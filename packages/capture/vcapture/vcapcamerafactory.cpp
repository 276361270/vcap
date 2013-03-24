#include "vcapcamerafactory.h"
#include "vcapfilter.h"
#include "vcapcamera.h"

std::vector<VCapCamera*>	VCapCameraFactory::enumCameras()
{
	std::vector<VCapCamera*> cameras;

	ICreateDevEnum*	pSysDevEnum=NULL;
	IEnumMoniker *	pEnumCat=NULL;
	IMoniker *		pMoniker=NULL;
	HRESULT			hr = S_OK;

	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void **)&pSysDevEnum);
	if( !pSysDevEnum || FAILED(hr) )
		return cameras;

	hr = pSysDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnumCat, 0);
	if( !pEnumCat || FAILED(hr) )
		return cameras;

	ULONG cFetched;
	while(pEnumCat->Next(1, &pMoniker, &cFetched) == S_OK)
	{
		VCapFilter*	filter = new VCapFilter(pMoniker);
		cameras.push_back( new VCapCamera(filter) );
	}

	return cameras;
}