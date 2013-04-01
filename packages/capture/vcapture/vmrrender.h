#ifndef VMRRender_H
#define VMRRender_H

#include "vcapconfig.h"

class DSFilter;
class VMRRender
{
public:
	VMRRender();
	~VMRRender();

public:
	void		init();
	void		setHWnd(HWND hWnd);
	void		paint();

public:
	DSFilter*	filter() { return m_pVMRFilter; }

private:	
	bool			m_bWindowless;
	HWND			m_hWnd;
	DSFilter*		m_pVMRFilter;
	IVMRWindowlessControl*	m_pVMRControl;
	IVMRFilterConfig*		m_pVMRConfig;
};


#endif