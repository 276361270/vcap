#ifndef FFMH264HANDLER_H
#define FFMH264HANDLER_H

#include "ffmconfig.h"

class FfmOutFormat;
class FfmH264Handler
{
public:
	FfmH264Handler();
	~FfmH264Handler();

public:
	void	setup(char* ip, int port, char* fmt, char* stream);
	int		onData(LONGLONG time, char* src, int inlen, char* dest, int outlen);
	void	close();
	void	setVideoSize(int width, int height);

private:
	void	dump_frame(AVFrame* frame);
	void	dump_packet(AVPacket* packet);

private:
	FfmOutFormat*		m_pOutFormat;
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
};

#endif