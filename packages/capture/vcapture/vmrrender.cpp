#include "vmrrender.h"
#include "dsfilter.h"

VMRRender::VMRRender()
{
	m_bWindowless = true;
	m_hWnd = NULL;
	m_pVMRFilter = NULL;
	m_pVMRControl = NULL;	
	m_pVMRConfig = NULL;

	init();
}


VMRRender::~VMRRender()
{
}

void	VMRRender::init()
{
	HRESULT		hr= S_OK;
	IBaseFilter* pVmr = NULL;	
	hr = CoCreateInstance(CLSID_VideoMixingRenderer, NULL, CLSCTX_INPROC, IID_IBaseFilter, (void**)&pVmr); 
	if( FAILED(hr) || !pVmr ) 
	{
		return;
	}
	m_pVMRFilter = new DSFilter(pVmr);
	
	hr = m_pVMRFilter->filter()->QueryInterface(IID_IVMRFilterConfig, (void**)&m_pVMRConfig); 
	if (SUCCEEDED(hr)) 
	{ 
		hr = m_pVMRConfig->SetRenderingMode(VMRMode_Windowless);
		m_pVMRConfig->Release();
		m_pVMRConfig = NULL;
	} 
	m_pVMRFilter->filter()->QueryInterface(IID_IVMRWindowlessControl, (void**)&m_pVMRControl); 
}

void	VMRRender::setHWnd(HWND hWnd)
{
	HRESULT		hr = S_OK;
	RECT src_rect, dest_rect;
	LONG width, height, arwidth, arheight;

	m_hWnd = hWnd;
	if( !m_pVMRControl ) 
		return;
	m_pVMRControl->GetNativeVideoSize(&width, &height, &arwidth, &arheight);
	hr = m_pVMRControl->SetVideoClippingWindow(m_hWnd);	

	
	dest_rect.left = 0;
	dest_rect.top = 0;
	dest_rect.right = width;
	dest_rect.bottom = height;
	::GetClientRect(m_hWnd, &dest_rect);
	m_pVMRControl->SetVideoPosition(NULL, &dest_rect);
}


void	VMRRender::paint()
{
	PAINTSTRUCT ps; 
	HDC		hdc; 
	RECT	rcClient; 
	RECT	rcDest;
	GetClientRect(m_hWnd, &rcClient); 
	hdc = BeginPaint(m_hWnd, &ps); 
	if (m_pVMRControl != NULL) 
	{ 
		HRGN rgnClient = CreateRectRgnIndirect(&rcClient); 
		HRGN rgnVideo = CreateRectRgnIndirect(&rcDest); 
		CombineRgn(rgnClient, rgnClient, rgnVideo, RGN_DIFF); 

		// Paint on window.
		HBRUSH hbr = GetSysColorBrush(COLOR_BTNFACE); 
		FillRgn(hdc, rgnClient, hbr); 
		// Clean up.
		DeleteObject(hbr); 
		DeleteObject(rgnClient); 
		DeleteObject(rgnVideo); 
		// Request the VMR to paint the video.
		HRESULT hr = m_pVMRControl->RepaintVideo(m_hWnd, hdc); 
	} 
	EndPaint(m_hWnd, &ps);
}