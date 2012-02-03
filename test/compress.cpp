#include <vision/image/image.h>
#include <vision/io/imageio.h>

#include <webp/encode.h>

#include <zlib.h>

#include <lzma.h>

#include <iostream>
#include <sstream>
#include <ctime>
#include <sys/time.h>

/* This test benchmarks a few losless compression algorithms on image data
   Rerun regularly to keep track of the updates of the different methods used

   Methods used:
    - WebP encoding
    - zlib compression
    - lzma compression

   Bench results: (Updated: 2012/02/03)
    - WebP (lossless):      1.2MB raw image -> 121kb compressed
                            ~400 ms to compress (2.5 fps)
    - zlib (Z_BEST_SPEED):  1.2MB raw image -> 720kb compressed
                            ~50 ms to compress (20 fps)
    - lzma (-0 & no check): 1.2MB raw image -> 472kb compressed
                            ~200 ms to compress (5 fps)
 */

inline void time_diff(const timeval & tv_in, const timeval & tv_out, timeval & tv_diff)
{
    if( tv_out.tv_sec < tv_in.tv_sec || (tv_out.tv_sec == tv_in.tv_sec && tv_out.tv_usec < tv_in.tv_usec) )
    {
        time_diff(tv_out, tv_in, tv_diff);
    }
    else
    {
        if(tv_out.tv_usec < tv_in.tv_usec)
        {
            tv_diff.tv_sec = tv_out.tv_sec - tv_in.tv_sec - 1;
            tv_diff.tv_usec = 1000000 - tv_in.tv_usec + tv_out.tv_usec;
        }
        else
        {
            tv_diff.tv_sec = tv_out.tv_sec - tv_in.tv_sec;
            tv_diff.tv_usec = tv_out.tv_usec - tv_in.tv_usec;
        }
    }
}

#define TIME_CALL(x) \
{ \
timeval tv_in;\
timeval tv_out;\
timeval tv_diff;\
gettimeofday(&tv_in, 0);\
x;\
gettimeofday(&tv_out, 0);\
time_diff(tv_in, tv_out, tv_diff);\
std::cout << "Call " << #x << " took: " << (tv_diff.tv_sec + ((float)tv_diff.tv_usec/1000000)) << "s" << std::endl;\
}

int WebPWriteToFile(const uint8_t* data, size_t data_size,
                                  const WebPPicture* const picture)
{
    std::ofstream * test = (std::ofstream*)(picture->custom_ptr);
    test->write((char *)data, data_size);
}

using namespace vision;

void usage(const char * prog_name)
{
    std::cerr << "[Usage] : " << prog_name << " [test image]" << std::endl;
}

int main(int argc, char * argv[])
{
    if(argc <= 1)
    {
        usage(argv[0]);
        return 1;
    }
    std::stringstream ss;
    ss << argv[1];
    std::string img_file = ss.str();
    Image<uint32_t, RGB> * img = new Image<uint32_t, RGB>();
    deserialize(img_file.c_str(), *img);

    /* WebP bench */
    WebPConfig config;
    if (!WebPConfigPreset(&config, WEBP_PRESET_PHOTO, 100))
    {
        return 0;   // version error
    }
    WebPPicture pic;
    if (!WebPPictureInit(&pic)) {
        return 0;    // version error
    }
    pic.width  = img->width;
    pic.height = img->height;
    pic.writer = WebPWriteToFile;
    std::ofstream test("test.webp", std::ios::binary | std::ios::out);
    pic.custom_ptr = (void*)&test;
    // allocated picture of dimension width x height
    if (!WebPPictureImportRGBA(&pic, (uint8_t *)img->raw_data, img->width*4)) {
        return 0;     // memory error
    }
    TIME_CALL(WebPEncode(&config, &pic));    
    test.close();


    /* zlib bench */
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree  = Z_NULL;
    strm.opaque = Z_NULL;
    int ret = deflateInit(&strm , Z_BEST_SPEED);
    if(ret != Z_OK)
    {
        std::cerr << "Error in deflateInit" << std::endl;
    }

    strm.avail_in = img->data_size;
    strm.next_in = (unsigned char *)(img->raw_data);
    unsigned char * zout = new unsigned char[img->data_size];
    int flush = Z_FINISH;
    strm.avail_out = img->data_size;
    strm.next_out = zout;

    TIME_CALL(ret = deflate(&strm, flush));
    assert(ret != Z_STREAM_ERROR);
    if(flush != Z_FINISH)
    {
        std::cerr << "flush != Z_FINISH : not normal " << std::endl;
    }
    unsigned int zsize = img->data_size - strm.avail_out;
    std::cout << "zlib compressed size: " << zsize << std::endl;

    /* lzma bench */
    unsigned int out_pos = 0;
    TIME_CALL(ret = lzma_easy_buffer_encode(0, LZMA_CHECK_NONE, NULL, (unsigned char*)(img->raw_data), img->data_size, zout, &out_pos, img->data_size));
    if(ret != LZMA_OK)
    {
        std::cerr << "LZMA compression failed !" << std::endl;
    }
    std::cout << "LZMA compressed size: " << out_pos << std::endl;

    delete[] zout;
    delete img;

    return 0;
}
