#ifndef VCAPVMRRENDER_H
#define VCAPVMRRENDER_H

#include "vcapconfig.h"

class VCapFilter;
class VCapVMRRender
{
public:
	VCapVMRRender();
	~VCapVMRRender();

public:
	void		init();
	void		setWindowless(bool wless);
	void		setHWnd(HWND hWnd);
	void		paint();

public:
	VCapFilter*	filter() { return m_pVMRFilter; }

private:	
	bool			m_bWindowless;
	HWND			m_hWnd;
	VCapFilter*		m_pVMRFilter;
	IVMRWindowlessControl*	m_pVMRControl;
	IVMRFilterConfig*		m_pVMRConfig;
};


#endif