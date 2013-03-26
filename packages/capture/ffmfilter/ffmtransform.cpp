#include "ffmtransform.h"

FfmTransform::FfmTransform()
{	
	m_pFormatContext = NULL;
	m_pCodecContext = NULL;
	m_pCodec = NULL;
	m_pStream = NULL;
}

FfmTransform::~FfmTransform()
{	
}

void	FfmTransform::open()
{
	::av_register_all();
	int ret = ::avformat_alloc_output_context2(&m_pFormatContext, NULL, "adts", NULL);
	m_pCodec = ::avcodec_find_encoder(AV_CODEC_ID_AAC);
	m_pStream = ::avformat_new_stream(m_pFormatContext, m_pCodec);
	m_pCodecContext = m_pStream->codec;

	m_pCodecContext->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;
	m_pCodecContext->sample_fmt = AV_SAMPLE_FMT_S16;
	m_pCodecContext->bit_rate = 40000;
	m_pCodecContext->sample_rate = 44100;
	m_pCodecContext->channels = 2;
	m_pCodecContext->gop_size = 21;
	//m_pCodecContext->profile = FF_PROFILE_AAC_MAIN;

	ret = ::avcodec_open2(m_pCodecContext, m_pCodec, NULL);

	m_nFrameSize = m_pCodecContext->frame_size*4;
}

int		FfmTransform::onData(int media_type, char* src, int inlen, char* dest, int outlen)
{
	int got_packet = 0;
	int ret = 0;
	int packets = inlen/m_nFrameSize;
	int num = 0;

	AVFrame *frame = avcodec_alloc_frame();
	frame->nb_samples = m_nFrameSize/4;
	av_init_packet(&m_packet);

	for( int i=0; i<packets; i++ ) {
		ret = ::avcodec_fill_audio_frame(frame, 2, AV_SAMPLE_FMT_S16, (uint8_t*)src + m_nFrameSize*i, m_nFrameSize, 1);
		ret = ::avcodec_encode_audio2(m_pCodecContext, &m_packet, frame, &got_packet);
		if( ret == 0 )
			num++;
	}

	return 0;
}