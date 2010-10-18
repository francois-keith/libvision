#include <iostream>

#include "image.h"
#include "visionprocess.h"

using namespace std ;

int main ( int argc, char** argv, char** envv ) {

	Image<unsigned char> imag(640,480) ;

	function(argc, argv, envv ) ;

	return 0 ;
}
