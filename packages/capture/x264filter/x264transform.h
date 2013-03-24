#ifndef X264TRANSFORM_H
#define X264TRANSFORM_H

#include "dsxfilter.h"

class X264Transform
{
public:
	X264Transform();
	~X264Transform();

public:
	void	open();
	int		onData(char* src, int inlen, char* dest, int outlen);

private:
	x264_param_t	m_param;
	x264_t*			m_pX264;
	x264_picture_t*	m_pPicIn;
	x264_picture_t*	m_pPicOut;
	x264_nal_t*		m_pNal;
};

#endif