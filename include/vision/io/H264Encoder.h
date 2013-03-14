#ifndef _H_H264ENCODER_H_
#define _H_H264ENCODER_H_

#include <vision/config.h>
#include <vision/image/image.h>

#include <stdint.h>

namespace vision
{

struct H264EncoderResult
{
public:
    H264EncoderResult() : frame_size(0), frame_data(0) {}
    int frame_size;
    uint8_t * frame_data;
};

}

#if Vision_HAS_LIBAVCODEC == 1

#ifndef UINT64_C
typedef uint64_t UINT64_C;
#endif

extern "C"
{
#include "x264.h"
#include "libswscale/swscale.h"
}

namespace vision 
{

class H264Encoder
{
public:
    H264Encoder(int width, int height, int fps);

    H264Encoder(x264_param_t * param);

    ~H264Encoder();

    H264EncoderResult Encode(vision::Image<uint32_t, vision::RGB> & img, uint64_t pts = 0);

    x264_picture_t * GetPicIn() { return &m_pic_in; }

    x264_picture_t * GetPicOut() { return &m_pic_out; }

    x264_param_t * GetParam() { return &m_param; }

    x264_t * GetEncoder() { return m_encoder; }
private:
    void Init(x264_param_t * param);

    int m_width;
    int m_height;
    int m_fps;
    int m_stride;

    struct SwsContext * m_convert_ctx;
 
    x264_param_t m_param;
    x264_t * m_encoder;
    x264_picture_t m_pic_in, m_pic_out;
}; 

} // namespace vision

#else

#pragma message ( "--- /!\\ --- You don't have libavcodec support with your libvision installation, don't use this header --- /!\\ ---")

namespace vision 
{

class H264Encoder
{
public:
    H264Encoder(int width, int height, int fps) {}

    ~H264Encoder() {}

    H264EncoderResult Encode(vision::Image<uint32_t, vision::RGB> & img) 
    {
        H264EncoderResult res;
        return res;
    }
}; 

} // namespace vision


#endif

#endif

