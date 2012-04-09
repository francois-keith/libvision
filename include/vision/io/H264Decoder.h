#ifndef _H_H264DecodeR_H_
#define _H_H264DecodeR_H_

#include <vision/config.h>

#if Vision_HAS_LIBAVCODEC == 1

#include <stdint.h>
#ifndef UINT64_C
typedef uint64_t UINT64_C;
#endif

extern "C"
{
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
#include "libavutil/opt.h"
#include "libavcodec/avcodec.h"
#include "libavutil/mathematics.h"
#include "libavutil/samplefmt.h"
}

#include <vision/image/image.h>

namespace vision 
{

class H264Decoder
{
public:
    H264Decoder(int width, int height);

    ~H264Decoder();

    int Decode(int frame_size, uint8_t * frame_data, vision::Image<uint32_t, vision::RGB> & img_out);
private:
    int m_width;
    int m_height;
    int m_stride;

    struct SwsContext * m_convert_ctx;
 
    AVCodec * codec;
    AVCodecContext * c;
    AVFrame *picture;
    AVPacket avpkt;
}; 

} // namespace vision

#else

#pragma message ( "--- /!\\ --- You don't have libavcodec support with your libvision installation, don't use this header --- /!\\ ---")

#endif

#endif

