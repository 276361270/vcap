#include "dscapture.h"

DSCapture::DSCapture()
{
	int ret;
	av_register_all();
	avdevice_register_all();
	avformat_network_init();
	AVInputFormat * a= av_find_input_format("dshow");	
	// Open the video file
	m_pInputFormatContext = NULL;
	if((ret= avformat_open_input(&m_pInputFormatContext, "video=Integrated Camera", a, NULL))!=0) {

	}

	::av_find_stream_info(m_pInputFormatContext);
	m_nInputAudioStreamIndex = ::av_find_best_stream(m_pInputFormatContext, AVMEDIA_TYPE_AUDIO, -1, -1, &m_pInputAudioCodec, 0);
	m_nInputVideoStreamIndex = ::av_find_best_stream(m_pInputFormatContext, AVMEDIA_TYPE_VIDEO, -1, -1, &m_pInputVideoCodec, 0);

	if( m_nInputAudioStreamIndex >= 0 ) {
		m_pInputAudioCodecContext = m_pInputFormatContext->streams[m_nInputAudioStreamIndex]->codec;
		::avcodec_open2(m_pInputAudioCodecContext, m_pInputAudioCodec, NULL);
	}
	if( m_nInputVideoStreamIndex >= 0 ) {
		m_pInputVideoCodecContext = m_pInputFormatContext->streams[m_nInputVideoStreamIndex]->codec;
		::avcodec_open2(m_pInputVideoCodecContext, m_pInputVideoCodec, NULL);
	}

	//output:
	ret = ::avformat_alloc_output_context2(&m_pOutputFormatContext, NULL, "flv", "rtmp://127.0.0.1:8080/live/live1");
	m_pOutputVideoCodec = ::avcodec_find_encoder(AV_CODEC_ID_H264);

	m_pOutputVideoStream = ::av_new_stream(m_pOutputFormatContext, 0);
	m_pOutputVideoCodecContext = m_pOutputVideoStream->codec;
	m_pOutputVideoCodecContext->pix_fmt = AV_PIX_FMT_YUV420P;
	m_pOutputVideoCodecContext->width = 320;
	m_pOutputVideoCodecContext->height = 240;
	m_pOutputVideoCodecContext->time_base.num = 1;
	m_pOutputVideoCodecContext->time_base.den = 25;
	m_pOutputVideoCodecContext->gop_size = 12;
	m_pOutputVideoCodecContext->bit_rate = 125000;
	m_pOutputVideoCodecContext->me_range = 16;
	m_pOutputVideoCodecContext->max_qdiff = 4;
	m_pOutputVideoCodecContext->qmax = 15;
	m_pOutputVideoCodecContext->qmin = 10;
	m_pOutputVideoCodecContext->qcompress = 0.6;
	m_pOutputVideoCodecContext->profile = FF_PROFILE_H264_BASELINE;
	if (m_pOutputFormatContext->oformat->flags & AVFMT_GLOBALHEADER)
		m_pOutputVideoCodecContext->flags |= CODEC_FLAG_GLOBAL_HEADER;
	if( m_pOutputVideoCodecContext->flags & AVFMT_GLOBALHEADER )
		m_pOutputVideoCodecContext->flags |= CODEC_FLAG_GLOBAL_HEADER;

	ret = ::avcodec_open2(m_pOutputVideoCodecContext, m_pOutputVideoCodec, NULL);
	ret = ::avio_open(&m_pOutputFormatContext->pb, "rtmp://127.0.0.1:8080/live/live1", AVIO_FLAG_WRITE);
	::avformat_write_header(m_pOutputFormatContext, NULL);

	//frame to hold the decoded data:
	m_pFrame = ::avcodec_alloc_frame();
	ret = avpicture_alloc((AVPicture*)m_pFrame, AV_PIX_FMT_YUV420P, 640, 480);

	//init the sws context:
	m_pSwsContext = sws_getContext(640, 480, AV_PIX_FMT_YUYV422,
		640, 480, AV_PIX_FMT_YUV420P, 
		SWS_BICUBIC, NULL, NULL, NULL);
	m_pMidFrame = ::avcodec_alloc_frame();
	ret = avpicture_alloc((AVPicture*)m_pMidFrame, AV_PIX_FMT_YUV420P, 640, 480);

	m_nBasePTS = 0;
}

DSCapture::~DSCapture()
{
	::av_write_trailer(m_pOutputFormatContext);
}

void	DSCapture::start()
{
	int ret = 0;
	int got_packet = 0;

	while(true) {
		::av_init_packet(&m_packet);
		ret = ::av_read_frame(m_pInputFormatContext, &m_packet);
		if( ret != 0 ) 
			continue;		
		//dump_packet(&m_packet);

		//convert from YUYV442 to YUV420P
		ret = avpicture_fill((AVPicture*)m_pFrame, (uint8_t*)m_packet.data, AV_PIX_FMT_YUYV422, 640, 480);
		if( ret < 0 ) {
			//FFMLOG("FfmH264Handler.onData, avpicture_fill failed with ret=", ret);
			return;
		}
		
		m_pMidFrame->pts = m_packet.pts;
		m_pMidFrame->pkt_pts = m_packet.pts;
		m_pMidFrame->pkt_dts = m_packet.dts;
		m_pMidFrame->width = 640;
		m_pMidFrame->height = 480;
		m_pMidFrame->pkt_size = m_packet.size;
		m_pMidFrame->pkt_duration = m_packet.duration;
		ret = sws_scale(m_pSwsContext, (const uint8_t * const *)m_pFrame->data, m_pFrame->linesize,
			0, 480, m_pMidFrame->data, m_pMidFrame->linesize);		
		
		::av_init_packet(&m_packet);
		ret = ::avcodec_encode_video2(m_pOutputVideoCodecContext, &m_packet, m_pMidFrame, &got_packet);
		if( ret == 0 && got_packet ) {
			/*
			if( m_nBasePTS == 0 ) {
				m_nBasePTS = m_packet.pts;
				m_packet.pts = 0;
				m_packet.dts = 0;				
			} else {
				m_packet.pts -= m_nBasePTS;
				m_packet.dts -= m_nBasePTS;
			}
			*/
			m_packet.pts/=100;
			m_packet.dts/=100;
			m_packet.stream_index = m_pOutputVideoStream->index;
			if( m_pOutputVideoCodecContext->coded_frame->key_frame ) {
				m_packet.flags = AV_PKT_FLAG_KEY;
				printf("key frame\r\n");
			}
			ret = ::av_interleaved_write_frame(m_pOutputFormatContext, &m_packet);
			dump_packet(&m_packet);
			//printf("frame size=%d, pts=%d\r\n", m_packet.size, m_packet.pts/1000);
		}
	}
}

void	DSCapture::stop()
{

}

void	DSCapture::dump_frame(AVFrame* frame) {
	time_t t;
	time(&t);
	printf("frame -%d - format=/key/pict_type=%d, %d, %d\r\n", t, frame->format, frame->key_frame, frame->pict_type);
	printf("frame - pts/pkt_pts/pkt_dts=%d, %d, %d\r\n", frame->pts, frame->pkt_pts, frame->pkt_dts);
}

void	DSCapture::dump_packet(AVPacket* packet) {
	time_t t;
	time(&t);
	printf("packet t/flags/duration/pts=%d, %lld, %d, %lld\r\n", t, packet->flags, packet->duration, packet->pts);
}