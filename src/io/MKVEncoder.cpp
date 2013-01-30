#include <vision/io/MKVEncoder.h>

#include <vision/io/H264Encoder.h>

extern "C"
{
#include "output/output.h"
}

namespace vision
{

struct MKVEncoderImpl
{
public:
    H264Encoder * encoder_;
    unsigned int encoded_frames_;
    unsigned int total_frames_;
    uint64_t pts_;
    hnd_t hout_;
public:
    MKVEncoderImpl(const std::string & file_out, int width, int height, int fps, unsigned int total_frames)
    : encoder_(0), encoded_frames_(0), total_frames_(total_frames), pts_(0), hout_(0)
    {
        cli_output_opt_t output_opt;
        memset( &output_opt, 0, sizeof(cli_output_opt_t) );

        if( mkv_output.open_file( const_cast<char*>(file_out.c_str()), &hout_, &output_opt ) )
        {
            std::cerr << "Failed to open " << file_out << std::endl;
            throw(std::string("Error"));
        }

        x264_param_t param_;
        x264_param_default_preset(&param_, "veryfast", "zerolatency");
        param_.i_threads = 0;
        param_.b_intra_refresh = 0;
        param_.b_repeat_headers = 0;
        param_.b_annexb = 0;
        param_.i_csp = X264_CSP_I420;
        param_.i_width = width;
        param_.i_height = height;
        param_.i_fps_num = fps;
        param_.i_fps_den = 1;
        // Intra refres:
        param_.i_keyint_max = fps;
        param_.b_intra_refresh = 1;
        //Rate control:
        param_.rc.i_rc_method = X264_RC_CRF;
        param_.rc.f_rf_constant = 25;
        param_.rc.f_rf_constant_max = 35;

        // Specific for video encoding
        param_.b_vfr_input = 1;
        param_.i_fps_num = fps;
        param_.i_fps_den = 1;
        param_.i_timebase_num = 1;
        param_.i_timebase_den = fps;
        param_.vui.i_sar_width  = 1;
        param_.vui.i_sar_height = 1;
        param_.i_frame_total = total_frames_;

        encoder_ = new H264Encoder(&param_);
        x264_param_apply_fastfirstpass( &param_ );
        x264_param_apply_profile(&param_, "baseline");
        if( mkv_output.set_param(hout_, &param_) )
        {
            std::cerr << "Failed to set_param no output" << std::endl;
            throw(std::string("Error"));
        }
        // Write SPS/PPS/SEI
        x264_nal_t *headers;
        int i_nal;

        if( x264_encoder_headers( encoder_->GetEncoder(), &headers, &i_nal ) < 0 )
        {
            std::cerr <<  "x264_encoder_headers failed" << std::endl;
            throw(std::string("Error"));
        }
        if( mkv_output.write_headers( hout_, headers ) < 0 )
        {
            std::cerr <<  "error writing headers to output file" << std::endl;
            throw(std::string("Error"));
        }
    }

    ~MKVEncoderImpl()
    {
        if(!total_frames_) { std::cout << "Encoded " << encoded_frames_ << std::endl; }
        else { std::cout << std::endl; }
        if(hout_) { mkv_output.close_file(hout_, 0, 0); }
        delete encoder_;
    }

    void EncodeFrame(vision::Image<uint32_t, vision::RGB> & img)
    {
        H264EncoderResult res = encoder_->Encode(img, pts_);
        pts_ = encoder_->GetPicIn()->i_pts;
        pts_++;
        if(res.frame_size)
        {
            mkv_output.write_frame( hout_, res.frame_data, res.frame_size, encoder_->GetPicOut() );
        }
        encoded_frames_++;
        if(total_frames_)
        {
            std::cout << "\rEncoded " << encoded_frames_ << " frames out of " << total_frames_ << std::flush;
        }
    }
};

MKVEncoder::MKVEncoder(const std::string & file_out, int width, int height, int fps, unsigned int total_frame)
: impl_(new MKVEncoderImpl(file_out, width, height, fps, total_frame))
{
}

MKVEncoder::~MKVEncoder() 
{
}

void MKVEncoder::EncodeFrame(vision::Image<uint32_t, vision::RGB> & img)
{
    impl_->EncodeFrame(img);
}

} // namespace vision

