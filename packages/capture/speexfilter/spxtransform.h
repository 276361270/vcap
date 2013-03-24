#ifndef SPXTRANSFORM_H
#define SPXTRANSFORM_H

#include "spxfilter.h"

class SpxTransform
{
public:
	SpxTransform();
	~SpxTransform();

public:
	void	open();
	int		onData(char* src, int inlen, char* dest, int outlen);

private:
	SpeexBits	m_bits;
	void*		m_encoder;
	int			m_sample_rate;
};

#endif