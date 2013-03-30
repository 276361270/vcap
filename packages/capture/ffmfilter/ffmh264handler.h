#ifndef FFMH264HANDLER_H
#define FFMH264HANDLER_H

#include "ffmconfig.h"

class FfmH264Nal;
class FfmH264Handler
{
public:
	FfmH264Handler();
	~FfmH264Handler();

public:
	void	open();
	int		onData(LONGLONG time, char* src, int inlen, char* dest, int outlen);
	void	close();

private:
	void	dump_frame(AVFrame* frame);
	void	dump_packet(AVPacket* packet);

private:
	AVFormatContext*	m_pFormatContext;
	AVCodecContext*		m_pCodecContext;
	AVCodec*			m_pCodec;
	AVStream*			m_pStream;
	AVPacket			m_packet;
	AVFrame*			m_pFrame;
	AVFrame*			m_pMidFrame;
	SwsContext*			m_pSwsContext;
	
	int					m_nSrcWidth;
	int					m_nSrcHeight;
	int					m_nDestWidth;
	int					m_nDestHeight;
	long long			m_nBasePTS;
};

#endif