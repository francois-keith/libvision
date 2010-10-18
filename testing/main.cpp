#include <iostream>

#include <visionlib/image.h>
#include <visionlib/visionprocess.h>

using namespace std ;

int main ( int argc, char** argv, char** envv ) {

	Image<unsigned char> imag(640,480) ;

	function(argc, argv, envv ) ;

	return 0 ;
}
