#include <vision/image/image.h>
#include <vision/io/imageio.h>

#include <iostream>
#include <sstream>
#include <ctime>

/* The aim of this test is to test the serialization and show how to use it */

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
    if(img_file == "/tmp/test.png")
    {
        std::cerr << "[Warning] I will use /tmp/test.png in this test and overwrite your image, do you want to continue ? (y/n) ";
        char c = 0;
        while(c != 'y' && c != 'n')
        {
            std::cin >> c;
        }
        if(c == 'n')
        {
            std::cerr << "[Warning] Ok, let's exit before we do something stupid" << std::endl;
            return 1;
        }
        else
        {
            std::cerr << "[Warning] You've been warned!" << std::endl;
        }
    }

    Image<uint32_t, RGB> * img_orig = load_color<uint32_t, RGB>(img_file);

    serialize("/tmp/test.bin", *img_orig);

    delete img_orig;

    Image<uint32_t, RGB> * new_img = new Image<uint32_t, RGB>();

    deserialize("/tmp/test.bin", *new_img);

    save_color<uint32_t, RGB>("/tmp/test.png", new_img);

    delete new_img;

    return 0;
}
