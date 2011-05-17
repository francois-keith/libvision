#include <vision/image/image.h>
#include <vision/io/imageio.h>

using namespace vision ;


int main ( int argc, char** argv ) {


Image<unsigned int> *img2 = load_color<unsigned int,RGB>( std::string(argv[1]) ) ;

save_color<unsigned int, RGB>( std::string(argv[2]) , img2 ) ;
save_mono<unsigned int, RGB>( std::string(argv[3]), img2 ) ;

return 0 ;

}
