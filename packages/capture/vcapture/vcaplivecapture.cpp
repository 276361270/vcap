#include "vcaplivecapture.h"
#include "vcapengine.h"
#include "vcapcamera.h"
#include "vcapenginefactory.h"
#include "vcapcamerafactory.h"
#include "vcapvideoencoderfactory.h"
#include "vcapvmrrender.h"
#include "vcapvideoencoder.h"
#include "vcapfilter.h"

VCapLiveCapture::VCapLiveCapture()
{
	m_pEngine = VCapEngineFactory::getInstance();	
	m_pCamera = NULL;
	m_pEncoder = VCapVideoEncoderFactory::findFilter(L"x264");
	m_pVMRRender = new VCapVMRRender();

	m_arrCameras = VCapCameraFactory::enumCameras();
	if( m_arrCameras.size() >= 1 )
		m_pCamera = m_arrCameras[0];	
}

VCapLiveCapture::~VCapLiveCapture()
{
	if( m_pVMRRender )
		delete m_pVMRRender;
	if( m_pEncoder )
		delete m_pEncoder;
}

int		VCapLiveCapture::startCapture(int hWnd)
{	
	HRESULT hr = S_OK;

	m_pVMRRender->setHWnd((HWND)hWnd);
	
	if( !m_pCamera )
		return VCAP_ERROR_NO_CAMERA;
	if( !m_pEncoder )
		return VCAP_ERROR_NO_X264_FILTER;

	m_pEngine->getGraphBuilder()->AddFilter( m_pCamera->filter()->filter(), L"Camera");
	m_pEngine->getGraphBuilder()->AddFilter( m_pEncoder->filter()->filter(), L"X264 Encoder");	
	//m_pEngine->getGraphBuilder()->AddFilter( m_pNetFilter->filter()->filter(), L"Net Writer");
	m_pEngine->getGraphBuilder()->AddFilter( m_pVMRRender->filter()->filter(), L"VMR9 Render");
	hr = m_pEngine->getCaptureBuilder()->RenderStream(&PIN_CATEGORY_CAPTURE, 
		&MEDIATYPE_Video, 
		m_pCamera->filter()->filter(), 
		m_pEncoder->filter()->filter(), 						
		NULL);

	hr = m_pEngine->getCaptureBuilder()->RenderStream(&PIN_CATEGORY_PREVIEW, 
		&MEDIATYPE_Video, 
		m_pCamera->filter()->filter(), 
		NULL,
		m_pVMRRender->filter()->filter() );

	m_pEngine->getMediaControl()->Run();

	return VCAP_ERROR_OK;
}

int		VCapLiveCapture::stopCapture()
{
	if( !m_pEngine || !m_pEngine->getMediaControl() )
		return VCAP_ERROR_UNKNOWN;

	m_pEngine->getMediaControl()->Stop();
	return VCAP_ERROR_OK;
}

void	VCapLiveCapture::paint()
{
	m_pVMRRender->paint();
}
