#include <vision/image/image.h>
#include <vision/io/imageio.h>

#include <iostream>
#include <sstream>
#include <ctime>

/* The aim of this test is to test the correspondance between two images */

using namespace vision;

void usage(const char * prog_name)
{
    std::cerr << "[Usage] : " << prog_name << " [left image] [right image]" << std::endl;
}

int main(int argc, char * argv[])
{
    if(argc <= 2)
    {
        usage(argv[0]);
        return 1;
    }

    std::stringstream ss_left;
    ss_left << argv[1];
    std::string img_left = ss_left.str();
    
    std::stringstream ss_right;
    ss_left << argv[2];
    std::string img_left = ss_right.str();
    

    Image<uint32_t, RGB> * img_left = load_color<uint32_t, RGB>(img_left);
    Image<uint32_t, RGB> * img_right = load_color<uint32_t, RGB>(img_right);


    save_color<uint32_t, RGB>("/tmp/test.png", img_left);
    save_color<uint32_t, RGB>("/tmp/test.png", img_right);


    delete img_left;
    delete img_right;

    return 0 ;


}
 
