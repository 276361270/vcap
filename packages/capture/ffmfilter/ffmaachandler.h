#ifndef FFMAACHANDLER_H
#define FFMAACHANDLER_H

#include "ffmconfig.h"
#include "icodechandler.h"

class FfmOutFormat;
class FfmAacHandler : public ICodecHandler
{
public:
	FfmAacHandler();
	~FfmAacHandler();

public:
	int		setup(char* ip, int port, char* fmt, char* stream);
	int		onData(LONGLONG time, char* src, int inlen, char* dest, int outlen);
	void	close();

private:
	FfmOutFormat*		m_pOutFormat;
	AVCodecContext*		m_pCodecContext;
	AVCodec*			m_pCodec;
	AVStream*			m_pStream;
	AVPacket			m_packet;
	AVFrame*			m_pFrame;
	int		m_nSampleRate;
	int		m_nBitRate;
	int		m_nChannels;
	int		m_nSamples;
};

#endif