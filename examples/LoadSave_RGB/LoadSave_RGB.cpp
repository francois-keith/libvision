#include <vision/vision.h>

using namespace vision ;

int main ( int argc, char** argv ) {

	if ( argc != 3 ) {
		cerr << "usage :" << endl ;
		cerr << "\t\t ./example_rgb inputfile outputfile" << endl ;
		return 0 ;
	}
	
	Image<unsigned int,RGB> *img = load_color<unsigned int, RGB>( std::string(argv[1]) ) ;
	save_color<unsigned int,RGB>(  std::string(argv[2]) , img ) ;
	return 0 ;
}
