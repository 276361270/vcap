#include "vcapvmrrender.h"
#include "vcapfilter.h"

VCapVMRRender::VCapVMRRender()
{
	m_bWindowless = true;
	m_hWnd = NULL;
	m_pVMRControl = NULL;	
	m_pVMRConfig = NULL;

	init();
}


VCapVMRRender::~VCapVMRRender()
{
}

void	VCapVMRRender::init()
{
	HRESULT		hr= S_OK;
	IBaseFilter* pVmr = NULL;	
	hr = CoCreateInstance(CLSID_VideoMixingRenderer, NULL, CLSCTX_INPROC, IID_IBaseFilter, (void**)&pVmr); 
	if( FAILED(hr) || !pVmr ) 
	{
		return;
	}
	m_pVMRFilter = new VCapFilter(pVmr);
	
	hr = m_pVMRFilter->filter()->QueryInterface(IID_IVMRFilterConfig, (void**)&m_pVMRConfig); 
    if (SUCCEEDED(hr)) 
    { 
        m_pVMRConfig->SetRenderingMode(VMRMode_Windowless);                 
    } 
	m_pVMRFilter->filter()->QueryInterface(IID_IVMRWindowlessControl, (void**)&m_pVMRControl); 
}

void	VCapVMRRender::setWindowless(bool wless)
{

}

void	VCapVMRRender::setHWnd(HWND hWnd)
{
	HRESULT		hr = S_OK;
	m_hWnd = hWnd;
	if( !m_pVMRControl ) 
		return;
	hr = m_pVMRControl->SetVideoClippingWindow(m_hWnd);	

	RECT rect;
	::GetClientRect(m_hWnd, &rect);
	m_pVMRControl->SetVideoPosition(NULL, &rect);
}


void	VCapVMRRender::paint()
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