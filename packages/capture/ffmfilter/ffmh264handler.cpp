#include "ffmh264handler.h"
#include "ffmoutformat.h"
#include "ffmrtmpoformat.h"
#include "ffmlog.h"

FfmH264Handler::FfmH264Handler()
{	
	m_pOutFormat = NULL;
	m_pCodecContext = NULL;
	m_pCodec = NULL;
	m_pStream = NULL;
	m_pFrame = NULL;

	m_nSrcWidth = 640;
	m_nSrcHeight = 480;
	m_nDestWidth = 160;
	m_nDestHeight = 120;
}

FfmH264Handler::~FfmH264Handler()
{	
	close();
}

int		FfmH264Handler::setup(char* ip, int port, char* app, char* stream) {
	int ret = 0;

	m_pOutFormat = new FfmRtmpOFormat(ip, port, app, stream);
	m_pCodec = ::avcodec_find_encoder(AV_CODEC_ID_H264);
	if( m_pCodec == NULL ) {
		FFMLOG("FfmH264Handler::setup, avcodec_find_encoder failed.");
		return -1;
	}

	m_pStream = ::avformat_new_stream(m_pOutFormat->getFormatContext(), m_pCodec);
	m_pCodecContext = m_pStream->codec;

	m_pCodecContext->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;
	m_pCodecContext->pix_fmt = AV_PIX_FMT_YUV420P;
	m_pCodecContext->bit_rate = 100000;
	m_pCodecContext->width = m_nDestWidth;
	m_pCodecContext->height = m_nDestHeight;
	m_pCodecContext->gop_size = 12;
	m_pCodecContext->time_base.num = 1;
	m_pCodecContext->time_base.den = 12;

	//x264 settings:
	m_pCodecContext->me_range = 16;
	m_pCodecContext->max_qdiff = 4;
	m_pCodecContext->qmax = 12;
	m_pCodecContext->qmin = 10;
	m_pCodecContext->qcompress = (float)0.6;
	m_pCodecContext->max_b_frames = 1;
	m_pCodecContext->keyint_min = 12;
	m_pCodecContext->profile = FF_PROFILE_H264_BASELINE;
	if (m_pOutFormat->getFormatContext()->oformat->flags & AVFMT_GLOBALHEADER)
		m_pCodecContext->flags |= CODEC_FLAG_GLOBAL_HEADER;

	ret = ::avcodec_open2(m_pCodecContext, m_pCodec, NULL);
	if( ret != 0 ) {
		FFMLOG("FfmH264Handler::open, avcodec_open2 failed with ret=", ret);
		return ret;
	}
	av_set_pts_info(m_pStream, 32, 1, 1000);  

	//init the frame objects:
	m_pFrame = avcodec_alloc_frame();
	ret = avpicture_alloc((AVPicture*)m_pFrame, AV_PIX_FMT_YUYV422, m_nSrcWidth, m_nSrcHeight);
	
	m_pMidFrame = avcodec_alloc_frame();
	ret = avpicture_alloc((AVPicture*)m_pMidFrame, AV_PIX_FMT_YUV420P, m_nDestWidth, m_nDestHeight);

	//we need to convert AV_PIX_FMT_YUYV422 to AV_PIX_FMT_YUV420P.
	m_pSwsContext = sws_getContext(m_nSrcWidth, m_nSrcHeight, AV_PIX_FMT_YUYV422,
		m_nDestWidth, m_nDestHeight, AV_PIX_FMT_YUV420P, 
		SWS_BICUBIC, NULL, NULL, NULL);

	m_pOutFormat->connectServer();

	return 0;
}

int		FfmH264Handler::onData(LONGLONG time, char* src, int inlen, char* dest, int outlen) {
	int got_packet = 0;
	int ret = 0;
	int num = 0;
	long long pts = time*9/1000;

	//ensure preview works:
	memcpy(dest, src, inlen);

	//Pix format transfer, as H264 only handle AV_PIX_FMT_YUV420P.
	ret = avpicture_fill((AVPicture*)m_pFrame, (uint8_t*)src, AV_PIX_FMT_YUYV422, m_nSrcWidth, m_nSrcHeight);
	if( ret < 0 ) {
		FFMLOG("FfmH264Handler.onData, avpicture_fill failed with ret=", ret);
		return 0;
	}

	m_pMidFrame->width = m_nDestWidth;
	m_pMidFrame->height = m_nDestHeight;
	m_pMidFrame->pts = pts;
	m_pMidFrame->pkt_pts = pts;
	m_pMidFrame->pkt_dts = pts;
	m_pMidFrame->pkt_duration = 1000*1000/m_pCodecContext->time_base.den;
	m_pMidFrame->pkt_size = inlen;
	sws_scale(m_pSwsContext, (const uint8_t * const *)m_pFrame->data, m_pFrame->linesize,
		0, m_nSrcHeight, m_pMidFrame->data, m_pMidFrame->linesize);

	//dump_frame(m_pMidFrame);
	av_init_packet(&m_packet);
	m_packet.size = 0;
	m_packet.data = NULL;
	ret = ::avcodec_encode_video2(m_pCodecContext, &m_packet, m_pMidFrame, &got_packet);
	if( ret == 0 && got_packet != 0 )
	{
		m_packet.stream_index = m_pStream->index;		
		m_packet.priv = NULL;

		if (m_pCodecContext->coded_frame->key_frame) {
			m_packet.flags |= AV_PKT_FLAG_KEY;
		}
		
		ret = ::av_interleaved_write_frame(m_pOutFormat->getFormatContext(), &m_packet);
		if( ret < 0 ) {
			FFMLOG("FfmH264Handler.onData, av_interleaved_write_frame failed with ret=", ret);
		}
		FFMLOG("FfmH264Handler.onData, pts", pts);
		num++;
	} else {
		FFMLOG("FfmH264Handler.onData, avcodec_encode_video2 failed with ret/got_packet=", ret, got_packet);
	}

	return 0;
}

void	FfmH264Handler::setVideoSize(int width, int height)
{
	m_nDestWidth = width;
	m_nDestHeight = height;
}

void	FfmH264Handler::close() {
	if( m_pCodecContext ) {
		avcodec_close(m_pCodecContext);
		m_pCodecContext = NULL;
	}
	if( m_pFrame ) {
		avcodec_free_frame(&m_pFrame);
		m_pFrame = NULL;
	}
}

void	FfmH264Handler::dump_frame(AVFrame* frame) {
	FFMLOG("frame - format/key/pict_type=", frame->format, frame->key_frame, frame->pict_type);
	FFMLOG("frame - pts/pkg_pts/pkt_dts=", frame->pts, frame->pkt_pts, frame->pkt_dts);
}

void	FfmH264Handler::dump_packet(AVPacket* packet) {
	FFMLOG("packet - flags/duration/pts=", packet->flags, packet->duration, packet->pts);
}