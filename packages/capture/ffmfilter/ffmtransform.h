#ifndef FFMTRANSFORM_H
#define FFMTRANSFORM_H

#include "ffmfilter.h"

class FfmTransform
{
public:
	FfmTransform();
	~FfmTransform();

public:
	void	open();
	int		onData(int media_type, char* src, int inlen, char* dest, int outlen);

private:
	AVFormatContext*	m_pFormatContext;
	AVCodecContext*		m_pCodecContext;
	AVCodec*			m_pCodec;
	AVStream*			m_pStream;
	AVPacket			m_packet;
	int					m_nFrameSize;
};

#endif