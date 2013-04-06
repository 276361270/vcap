#include "ffmaachandler.h"
#include "ffmoutformat.h"
#include "ffmrtmpoformat.h"
#include "ffmbuffer.h"
#include "ffmlog.h"

FfmAacHandler::FfmAacHandler()
{	
	m_pOutFormat = NULL;
	m_pCodecContext = NULL;
	m_pCodec = NULL;
	m_pStream = NULL;
	m_pFrame = NULL;
	m_nSampleRate = 44100;
	m_nBitRate = 40000;
	m_nChannels = 2;
	m_nSamples = m_nSampleRate*20/1000;
	m_nFrameSize = 0;
	m_pBuffer = NULL;
}

FfmAacHandler::~FfmAacHandler()
{	
	close();
}

int		FfmAacHandler::setup(char* ip, int port, char* fmt, char* stream) {
	int ret = 0;

	m_pOutFormat = new FfmRtmpOFormat(ip, port, fmt, stream);
	m_pCodec = ::avcodec_find_encoder(AV_CODEC_ID_AAC);

	m_pStream = ::avformat_new_stream(m_pOutFormat->getFormatContext(), m_pCodec);
	m_pCodecContext = m_pStream->codec;

	m_pCodecContext->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;
	//m_pCodecContext->profile = FF_PROFILE_AAC_LOW;
	m_pCodecContext->sample_fmt = AV_SAMPLE_FMT_S16;
	m_pCodecContext->bit_rate = m_nBitRate;
	m_pCodecContext->sample_rate = m_nSampleRate;
	m_pCodecContext->channels = m_nChannels;
	m_pCodecContext->gop_size = 50;
	if (m_pOutFormat->getFormatContext()->oformat->flags & AVFMT_GLOBALHEADER)
		m_pCodecContext->flags |= CODEC_FLAG_GLOBAL_HEADER;

	ret = ::avcodec_open2(m_pCodecContext, m_pCodec, NULL);
	if( ret != 0 ) {
		FFMLOG("FfmAacHandler.onData, avcodec_open2 failed with ret=", ret);
		return ret;
	}
	av_set_pts_info(m_pStream, 32, 1, 1000); 

	m_nFrameSize = m_pCodecContext->frame_size;
	if( m_nFrameSize == 0 ) {
		m_nFrameSize = m_nSamples;
	}
	m_pBuffer = new FfmBuffer(m_nFrameSize*m_nChannels*2);
	m_pFrame = avcodec_alloc_frame();

	m_pOutFormat->connectServer();

	return 0;
}

int		FfmAacHandler::onData(LONGLONG time, char* src, int inlen, char* dest, int outlen) {
	int got_packet = 0;
	int ret = 0;
	int num = 0;
	long long pts = time*9/1000;
	int samples = m_nFrameSize*m_nChannels*av_get_bytes_per_sample(AV_SAMPLE_FMT_S16);
	char* sample_buf = NULL;

	//construct the samples, maybe inlen<m_nFrameSize*4;
	m_pBuffer->push(src, inlen);
	sample_buf = m_pBuffer->pop();

	if( sample_buf == NULL ) {
		FFMLOG("FfmAacHandler.onData, not enough data.");
		return -1;
	}
	avcodec_get_frame_defaults(m_pFrame);
	m_pFrame->nb_samples = m_nFrameSize;
	ret = ::avcodec_fill_audio_frame(m_pFrame, m_pCodecContext->channels, m_pCodecContext->sample_fmt, (uint8_t*)sample_buf, samples, 1);
	if( ret != 0 ) {
		FFMLOG("FfmAacHandler.onData, avcodec_fill_audio_frame failed with ret=", ret);
		return 0;
	}

	av_init_packet(&m_packet);
	m_packet.size = 0;
	m_packet.data = NULL;
	ret = ::avcodec_encode_audio2(m_pCodecContext, &m_packet, m_pFrame, &got_packet);
	if( ret == 0 && got_packet )
	{
		m_pFrame->pts = pts;
		m_packet.stream_index = m_pStream->index;
		m_packet.priv = NULL;

		ret = ::av_interleaved_write_frame(m_pOutFormat->getFormatContext(), &m_packet);
		if( ret < 0 ) {
			FFMLOG("FfmAacHandler.onData, av_write_frame failed with ret=", ret);
		}
		FFMLOG("FfmAacHandler.onData, pts", pts);
		num++;
	} else {
		FFMLOG("FfmAacHandler.onData, avcodec_encode_audio2 failed with ret=", ret);
	}

	return 0;
}

void	FfmAacHandler::close() {
	if( m_pCodecContext ) {
		avcodec_close(m_pCodecContext);
		m_pCodecContext = NULL;
	}
	if( m_pFrame ) {
		avcodec_free_frame(&m_pFrame);
		m_pFrame = NULL;
	}
}
