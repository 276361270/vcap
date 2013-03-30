#ifndef DSCAPTURE_H
#define DSCAPTURE_H

#include "stdafx.h"

extern "C"{
#ifdef __cplusplus
#define __STDC_CONSTANT_MACROS
#ifdef _STDINT_H
#undef _STDINT_H
#endif
# include <stdint.h>
#endif
}

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavutil/avutil.h"
#include "libavutil/dict.h"
#include "libavformat/avformat.h"
#include "libavdevice/avdevice.h"
#include "libswscale/swscale.h"
};

class DSCapture
{
public:
	DSCapture();
	~DSCapture();

public:
	void	start();
	void	stop();	

private:
	void	dump_frame(AVFrame* frame);
	void	dump_packet(AVPacket* packet);

private:
	AVFormatContext*	m_pInputFormatContext;
	AVCodec*			m_pInputAudioCodec;
	AVCodec*			m_pInputVideoCodec;
	AVCodecContext*		m_pInputAudioCodecContext;
	AVCodecContext*		m_pInputVideoCodecContext;
	int					m_nInputAudioStreamIndex;
	int					m_nInputVideoStreamIndex;
	AVPacket			m_packet;
	AVFrame*			m_pFrame;

	AVFormatContext*	m_pOutputFormatContext;
	AVCodec*			m_pOutputVideoCodec;
	AVCodecContext*		m_pOutputVideoCodecContext;
	AVStream*			m_pOutputVideoStream;

	SwsContext*			m_pSwsContext;
	AVFrame*			m_pMidFrame;
	long long			m_nBasePTS;
};

#endif