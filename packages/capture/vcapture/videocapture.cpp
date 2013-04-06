#include "videocapture.h"
#include "engine.h"
#include "camera.h"
#include "camerafactory.h"
#include "vmrrender.h"
#include "filefilter.h"
#include "dsfilter.h"
#include "ffmencoder.h"

VideoCapture::VideoCapture()
{
	//m_pEngine = engine;	
	m_pEngine = NULL;
	m_pCamera = NULL;
	m_pEncoder = NULL;

	m_pFileFilter = NULL;
	m_pVMRRender = NULL;

	m_strIp = "127.0.0.1";
	m_nPort = 8080;
	m_strApp = "live";
	m_strStream = "live1";
}

VideoCapture::~VideoCapture()
{
	if( m_pVMRRender )
		delete m_pVMRRender;
	if( m_pEncoder )
		delete m_pEncoder;
	if( m_pFileFilter )
		delete m_pFileFilter;	
	if( m_pEngine ) 
		delete m_pEngine;
	if( m_pCamera ) 
		delete m_pCamera;
}

void	VideoCapture::setFileName(const wchar_t* filename)
{
	m_wstrFileName.assign(filename);
}

void	VideoCapture::setServer(char* ip, int port, char* app, char* stream)
{
	m_strIp = ip;
	m_nPort = port;
	m_strApp = app;
	m_strStream = stream;
}

int		VideoCapture::startCapture(int hWnd)
{	
	HRESULT hr = S_OK;
	int ret = VCAP_ERROR_OK;

	m_arrCameras = CameraFactory::enumCameras();
	if( m_arrCameras.size() >= 1 ) {
		m_pCamera = m_arrCameras[0];
	} else {
		return VCAP_ERROR_NO_CAMERA;
	}

	m_pEngine = new Engine();
	m_pEncoder = new FfmEncoder();
	ret = m_pEncoder->setup(FFM_MEDIA_VIDEO, const_cast<char*>(m_strIp.c_str()), m_nPort, const_cast<char*>(m_strApp.c_str()), const_cast<char*>(m_strStream.c_str()) );
	if( ret != VCAP_ERROR_OK ) {
		return ret;
	}

	m_pVMRRender = new VMRRender();
	m_pVMRRender->setHWnd((HWND)hWnd);
	if( m_wstrFileName.size() != 0 ) {
		m_pFileFilter = new FileFilter(m_pEngine, m_wstrFileName.c_str());
	}

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