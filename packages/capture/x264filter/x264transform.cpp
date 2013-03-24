#include "x264transform.h"

X264Transform::X264Transform()
{
	x264_param_default(&m_param);
	m_param.i_threads = 1;
	m_param.i_frame_total = 0;
	m_param.i_width  = 320;
	m_param.i_height = 240;
	//m_param.i_fps_num = 10;
	m_param.i_log_level = X264_LOG_NONE;
	
}

X264Transform::~X264Transform()
{
	if( m_pX264 ) 
	{
		x264_picture_clean( m_pPicIn );
		x264_encoder_close( m_pX264 );
	}
}

void	X264Transform::open()
{
	m_pX264 = ::x264_encoder_open(&m_param);
	m_pPicIn = new x264_picture_t;
	x264_picture_alloc( m_pPicIn, X264_CSP_I420, m_param.i_width, m_param.i_height );	
	m_pPicOut = new x264_picture_t;
	x264_picture_alloc( m_pPicOut, X264_CSP_I420, m_param.i_width, m_param.i_height );	
}

int		X264Transform::onData(char* src, int inlen, char* dest, int outlen)
{
	int ret = 0;
	int i_nal = 0;
	char*	dest_temp = dest;
	x264_picture_init(m_pPicIn);

	m_pPicIn->img.i_csp = X264_CSP_I420;
	m_pPicIn->img.i_plane = 3;
	m_pPicIn->img.plane[0] = (uint8_t*)src;
	m_pPicIn->img.plane[1] = (uint8_t*)(src + m_param.i_width*m_param.i_height/4);
	m_pPicIn->img.plane[2] = (uint8_t*)(src + m_param.i_width*m_param.i_height/4);

	ret = x264_encoder_encode(m_pX264, &m_pNal, &i_nal, m_pPicIn, m_pPicOut);
	for( int i=0; i<i_nal; i++ ) 
	{
		x264_nal_encode(m_pX264, (uint8_t*)dest_temp, m_pNal);
	}

	return 0;
}