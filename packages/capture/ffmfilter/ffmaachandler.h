#ifndef FFMAACHANDLER_H
#define FFMAACHANDLER_H

#include "ffmconfig.h"

class FfmAacHandler
{
public:
	FfmAacHandler();
	~FfmAacHandler();

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
	int		m_nSampleRate;
	int		m_nBitRate;
	int		m_nChannels;
	
	int		m_nFrameSize;
	int		m_nSamples;
};

#endif