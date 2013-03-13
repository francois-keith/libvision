#ifndef _H_MKVENCODER_H_
#define _H_MKVENCODER_H_

#include <vision/config.h>

#if Vision_HAS_LIBAVCODEC == 1

#include <stdint.h>
#ifndef UINT64_C
typedef uint64_t UINT64_C;
#endif

#include <vision/io/H264Encoder.h>
#include <vision/image/image.h>

#include <boost/shared_ptr.hpp>

namespace vision 
{

struct MKVEncoderImpl;

class MKVEncoder
{
public:
    MKVEncoder(const std::string & file_out, int width, int height, int fps, unsigned int total_frame = 0);

    ~MKVEncoder();

    void EncodeFrame(vision::Image<uint32_t, vision::RGB> & img);
private:
    boost::shared_ptr<MKVEncoderImpl> impl_;
}; 

} // namespace vision

#else

#pragma message ( "--- /!\\ --- You don't have libavcodec support with your libvision installation, don't use this header --- /!\\ ---")

#include <string>
#include <vision/image/image.h>
#include <stdint.h>

namespace vision 
{

struct x264_param_t;

class MKVEncoder
{
private:
    MKVEncoder(const std::string & file_out, int width, int height, int fps) {}

    MKVEncoder(const std::string & file_out, x264_param_t * param) {}

    ~MKVEncoder() {}

    void EncodeFrame(vision::Image<uint32_t, vision::RGB> & img, uint64_t pts = 0) {}
}; 

} // namespace vision


#endif

#endif

