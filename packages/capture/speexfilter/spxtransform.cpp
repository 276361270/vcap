#include "spxtransform.h"

SpxTransform::SpxTransform()
{		
	m_sample_rate = 22050;
}

SpxTransform::~SpxTransform()
{
	speex_bits_destroy(&m_bits);
	speex_encoder_destroy(m_encoder);
}

void	SpxTransform::open()
{
	speex_bits_init(&m_bits);
	m_encoder = speex_encoder_init(&speex_nb_mode);

	int sample_rate = 22050;
	speex_encoder_ctl(m_encoder, SPEEX_SET_SAMPLING_RATE, &m_sample_rate);	
}

int		SpxTransform::onData(char* src, int inlen, char* dest, int outlen)
{
	int len = 0;
	speex_bits_reset(&m_bits);
	speex_encode_int(m_encoder, (short*)src, &m_bits);
	len = speex_bits_write(&m_bits, dest, outlen);
	return len;
}