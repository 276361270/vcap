#include "ffmh264handler.h"
#include "ffmlog.h"

FfmH264Handler::FfmH264Handler()
{	
	m_pFormatContext = NULL;
	m_pCodecContext = NULL;
	m_pCodec = NULL;
	m_pStream = NULL;
	m_pFrame = NULL;

	m_nWidth = 640;
	m_nHeight = 480;
	m_nPts = 0;
	m_nFrameIndex = 0;
	::av_register_all();
}

FfmH264Handler::~FfmH264Handler()
{	
	close();
}

void	FfmH264Handler::open() {
	char* filename = "d:\\out.ts";
	int ret = ::avformat_alloc_output_context2(&m_pFormatContext, NULL, NULL, filename);

	m_pCodec = ::avcodec_find_encoder(AV_CODEC_ID_H264);

	m_pStream = ::avformat_new_stream(m_pFormatContext, m_pCodec);
	m_pCodecContext = m_pStream->codec;

	m_pCodecContext->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;
	m_pCodecContext->pix_fmt = AV_PIX_FMT_YUV420P;
	m_pCodecContext->bit_rate = 500000;
	m_pCodecContext->width = m_nWidth;
	m_pCodecContext->height = m_nHeight;
	m_pCodecContext->channels = 2;
	m_pCodecContext->gop_size = 12;
	m_pCodecContext->time_base.num = 1;
	m_pCodecContext->time_base.den = 25;

	m_pCodecContext->dct_algo = 0;

	m_pCodecContext->gop_size = 1;
	m_pCodecContext->me_pre_cmp = 2;
	m_pCodecContext->me_method=7;
	m_pCodecContext->me_range = 16;
	m_pCodecContext->max_qdiff = 4;
	m_pCodecContext->qmin = 10;
	m_pCodecContext->qmax = 51;
	m_pCodecContext->qcompress = 0.6;
	m_pCodecContext->nsse_weight = 8;
	m_pCodecContext->i_quant_factor = (float)0.8;
	m_pCodecContext->b_quant_factor = 1.25;
	m_pCodecContext->b_quant_offset = 1.25;
	if (m_pFormatContext->oformat->flags & AVFMT_GLOBALHEADER)
		m_pCodecContext->flags |= CODEC_FLAG_GLOBAL_HEADER;

	ret = ::avcodec_open2(m_pCodecContext, m_pCodec, NULL);
	if( ret != 0 ) {
		FFMLOG("FfmH264Handler::open, avcodec_open2 failed with ret=", ret);
		return;
	}

	ret = ::avio_open(&m_pFormatContext->pb, filename, AVIO_FLAG_WRITE);
	if( ret != 0 ) {
		FFMLOG("FfmH264Handler::open, avio_open failed ret=", ret);
		return;
	}
	::avformat_write_header(m_pFormatContext, NULL);
	ret = avpicture_alloc(&m_picture, AV_PIX_FMT_YUYV422, m_nWidth, m_nHeight);
}

int		FfmH264Handler::onData(char* src, int inlen, char* dest, int outlen) {
	int got_packet = 0;
	int ret = 0;
	int num = 0;

	memcpy(dest, src, inlen);
	av_init_packet(&m_packet);
	int size = avpicture_get_size(AV_PIX_FMT_YUYV422, m_nWidth, m_nHeight);
	//::avpicture_alloc(&m_picture, AV_PIX_FMT_YUYV422, m_nWidth, m_nHeight);
	ret = avpicture_fill(&m_picture, (uint8_t*)src, AV_PIX_FMT_YUYV422, m_nWidth, m_nHeight);
	if( ret < 0 ) {
		FFMLOG("FfmH264Handler.onData, avpicture_fill failed with ret=", ret);
		return 0;
	}
	m_pFrame = (AVFrame*)&m_picture;
	m_pFrame->nb_samples = m_nWidth*m_nHeight*2;
	m_pFrame->pts = av_rescale(m_nFrameIndex++,AV_TIME_BASE*(int64_t)m_pCodecContext->time_base.num, m_pCodecContext->time_base.den);
	m_pFrame->pict_type = AV_PICTURE_TYPE_NONE;

	if (m_pFormatContext->oformat->flags & AVFMT_RAWPICTURE) {
		/* Raw video case - directly store the picture in the packet */
		m_packet.flags        |= AV_PKT_FLAG_KEY;
		m_packet.stream_index  = m_pStream->index;
		m_packet.data          = m_picture.data[0];
		m_packet.size          = sizeof(AVPicture);

		ret = av_interleaved_write_frame(m_pFormatContext, &m_packet);
	}  else { 
		ret = ::avcodec_encode_video2(m_pCodecContext, &m_packet, m_pFrame, &got_packet);
		if( ret == 0 && got_packet )
		{
			if (m_pCodecContext->coded_frame->key_frame)
				m_packet.flags |= AV_PKT_FLAG_KEY;

			m_packet.stream_index = m_pStream->index;
			ret = ::av_interleaved_write_frame(m_pFormatContext, &m_packet);
			if( ret < 0 ) {
				FFMLOG("FfmH264Handler.onData, avcodec_encode_audio2 failed with ret=", ret);
			}
			num++;
		} else {
			//	FFMLOG("FfmH264Handler.onData, avcodec_encode_audio2 failed with ret=", ret);
		}
	}
	//::avpicture_free(&m_picture);
	FFMLOG("FfmTransform.onData, inlen/frames=", inlen, num);

	return 0;
}

void	FfmH264Handler::close() {
	::av_write_trailer(m_pFormatContext);
	if( m_pCodecContext ) {
		avcodec_close(m_pCodecContext);
		m_pCodecContext = NULL;
	}
	if( m_pFormatContext ) {
		avio_close(m_pFormatContext->pb);
		avformat_free_context(m_pFormatContext);
		m_pFormatContext = NULL;
	}	
	if( m_pFrame ) {
		avcodec_free_frame(&m_pFrame);
		m_pFrame = NULL;
	}
}
