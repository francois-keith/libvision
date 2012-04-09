#include "vision/config.h"

#if Vision_HAS_LIBAVCODEC == 1

#include "vision/io/H264Decoder.h"

namespace vision
{

H264Decoder::H264Decoder(int width, int height)
: m_width(width), m_height(height)
{
    m_stride = 4*m_width;

    /* For YUV420P -> RGBA conversion */
    m_convert_ctx = sws_getContext(m_width, m_height, PIX_FMT_YUV420P, m_width, m_height, PIX_FMT_RGBA, SWS_FAST_BILINEAR, NULL, NULL, NULL);

    av_init_packet(&avpkt);

    /* Find H264 codec */
    avcodec_register_all();
    codec = avcodec_find_decoder(CODEC_ID_H264);
    if(!codec)
    {
        throw(std::string("H264 codec not found, check that your ffmpeg is built with H264 support"));
    }

    c = avcodec_alloc_context3(codec);
    picture = avcodec_alloc_frame();
    c->width  = m_width;
    c->height = m_height;

    if(avcodec_open2(c, codec, 0) < 0)
    {
        throw(std::string("Cannot open codec"));
    }
}

H264Decoder::~H264Decoder()
{
    avcodec_close(c);
    av_free(c);
    av_free(picture);
}
    
int H264Decoder::Decode(int frame_size, uint8_t * frame_data, vision::Image<uint32_t, vision::RGB> & img_out)
{
    avpkt.size = frame_size;
    avpkt.data = frame_data;
    int got_picture;
    int len = avcodec_decode_video2(c, picture, &got_picture, &avpkt);
    if(len < 0)
    {
        return len;
    }
    uint8_t *buf_out[4]={(uint8_t*)img_out.raw_data,NULL,NULL,NULL};
    sws_scale(m_convert_ctx, (const uint8_t* const*)picture->data, picture->linesize, 0, m_height, buf_out, &m_stride);
    return len;
}

} // namespace vision

#endif // Vision_HAS_LIBAVCODEC

