#include "camerafactory.h"
#include "dsfilter.h"
#include "camera.h"

std::vector<Camera*>	CameraFactory::enumCameras()
{
	std::vector<Camera*> cameras;

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
		DSFilter*	filter = new DSFilter(pMoniker);
		cameras.push_back( new Camera(filter) );
	}

	return cameras;
}