#include "videocapture.h"
#include "engine.h"
#include "camera.h"
#include "enginefactory.h"
#include "camerafactory.h"
#include "vmrrender.h"
#include "filefilter.h"
#include "dsfilter.h"
#include "ffmencoder.h"

VideoCapture::VideoCapture()
{
	m_pEngine = EngineFactory::getInstance();	
	m_pCamera = NULL;
	m_pEncoder = new FfmEncoder(FFM_MEDIA_VIDEO);
	m_pFileFilter = NULL;
	m_pVMRRender = new VMRRender();

	m_arrCameras = CameraFactory::enumCameras();
	if( m_arrCameras.size() >= 1 )
		m_pCamera = m_arrCameras[0];	
}

VideoCapture::~VideoCapture()
{
	if( m_pVMRRender )
		delete m_pVMRRender;
	if( m_pEncoder )
		delete m_pEncoder;
	if( m_pFileFilter )
		delete m_pFileFilter;	
}

void	VideoCapture::setFileName(const wchar_t* filename)
{
	m_wstrFileName.assign(filename);
}

void	VideoCapture::setVideoFormat(int format)
{

}

int		VideoCapture::startCapture(int hWnd)
{	
	HRESULT hr = S_OK;

	m_pVMRRender->setHWnd((HWND)hWnd);
	if( m_wstrFileName.size() != 0 ) {
		m_pFileFilter = new FileFilter(m_pEngine, m_wstrFileName.c_str());
	}
	
	if( !m_pCamera )
		return VCAP_ERROR_NO_CAMERA;
	if( !m_pEncoder )
		return VCAP_ERROR_NO_X264_FILTER;

	m_pEngine->getGraphBuilder()->AddFilter( m_pCamera->filter()->filter(), L"Camera");
	m_pEngine->getGraphBuilder()->AddFilter( m_pEncoder->filter()->filter(), L"Ffm Encoder");
	if( m_pFileFilter ) {
		m_pEngine->getGraphBuilder()->AddFilter( m_pFileFilter->filter()->filter(), L"File Writer");
	}
	m_pEngine->getGraphBuilder()->AddFilter( m_pVMRRender->filter()->filter(), L"VMR9 Render");
	
	hr = m_pEngine->getCaptureBuilder()->RenderStream(&PIN_CATEGORY_PREVIEW, 
		&MEDIATYPE_Video, 
		m_pCamera->filter()->filter(), 
		m_pEncoder->filter()->filter(),
		m_pVMRRender->filter()->filter()  );

	m_pEngine->start();

	return VCAP_ERROR_OK;
}

int		VideoCapture::stopCapture()
{
	if( !m_pEngine || !m_pEngine->getMediaControl() )
		return VCAP_ERROR_UNKNOWN;

	m_pEngine->stop();
	return VCAP_ERROR_OK;
}

void	VideoCapture::paint()
{
	m_pVMRRender->paint();
}
