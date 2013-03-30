#include "vcapcamera.h"
#include "vcapfilter.h"
#include "vcappin.h"

VCapCamera::VCapCamera(VCapFilter* filter)
: m_pFilter(filter)
, m_pCameraControl(NULL)
, m_pStreamConfig(NULL)
{
	HRESULT hr = S_OK;
	m_pFilter->filter()->QueryInterface(IID_IAMCameraControl, (void**)&m_pCameraControl);
	memset(&m_propExpose, 0, sizeof(m_propExpose));
	memset(&m_propZoon, 0, sizeof(m_propZoon));
	memset(&m_propIris, 0 , sizeof(m_propIris));
	getRanges();

	m_pOutPin = m_pFilter->getOutputPin();
	if( !m_pOutPin )
		return;	
	m_pOutPin->pin()->QueryInterface(IID_IAMStreamConfig , (void**)&m_pStreamConfig);

	AM_MEDIA_TYPE *media;
	m_pStreamConfig->GetFormat(&media);
	m_guidType = media->majortype;
	m_guidSubType = media->subtype;
	m_guidFormat = media->formattype;
	memcpy(&m_videoInfoHeader, media->pbFormat, media->cbFormat);

	//set the video properties:
	m_videoInfoHeader.AvgTimePerFrame = 100*10*1000;
	//m_videoInfoHeader.bmiHeader.biWidth = 480;
	//m_videoInfoHeader.bmiHeader.biHeight = 320;
	//hr = m_pStreamConfig->SetFormat(media);
}

VCapCamera::~VCapCamera()
{
}

void	VCapCamera::getRanges()
{	
	if( !m_pCameraControl ) 
		return;		

	m_pCameraControl->GetRange(CameraControl_Exposure, &m_propExpose.min, &m_propExpose.max, &m_propExpose.step, &m_propExpose.def, &m_propExpose.flags);
	m_pCameraControl->GetRange(CameraControl_Zoom, &m_propZoon.min, &m_propZoon.max, &m_propZoon.step, &m_propZoon.def, &m_propZoon.flags);
	m_pCameraControl->GetRange(CameraControl_Iris, &m_propIris.min, &m_propIris.max, &m_propIris.step, &m_propIris.def, &m_propIris.flags);
}

void	VCapCamera::setExpose(int expose)
{
	if( !m_pCameraControl )
		return;
	
	m_pCameraControl->Set(CameraControl_Exposure, expose, CameraControl_Flags_Manual);
}

void	VCapCamera::setAutoExpose()
{
	if( !m_pCameraControl )
		return;
	
	m_pCameraControl->Set(CameraControl_Exposure, 0, CameraControl_Flags_Auto);
}