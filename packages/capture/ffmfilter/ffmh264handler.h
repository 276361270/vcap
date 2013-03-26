#ifndef FFMH264HANDLER_H
#define FFMH264HANDLER_H

#include "ffmconfig.h"

class FfmH264Handler
{
public:
	FfmH264Handler();
	~FfmH264Handler();

public:
	void	open();
	int		onData(char* src, int inlen, char* dest, int outlen);
	void	close();

private:
	AVFormatContext*	m_pFormatContext;
	AVCodecContext*		m_pCodecContext;
	AVCodec*			m_pCodec;
	AVStream*			m_pStream;
	AVPacket			m_packet;
	AVFrame*			m_pFrame;
	AVPicture			m_picture;
	AVPicture			m_rawPicture;
	
	int		m_nWidth;
	int		m_nHeight;
	int		m_nPts;
	int		m_nFrameIndex;
};

#endif