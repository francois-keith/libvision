#include <iostream>
#include <cstring>
#include <vision/config.h>

using namespace std ;


void display_help() {
	cout << "aide" << endl ;
}


int main ( int argc, char** argv ) {

	if ( argc == 1 )
		display_help() ;
	
	for (int i=1; i<argc; i++ )
	
	if ( strcmp( argv[i], "--libs") == 0 ) {
			cout << " -l" << Vision_LIBS ;
			#if ( Vision_IMAGEMAGICK == TRUE )
				cout << " "<< Vision_IMAGEMAGICK_LIBS ;
			#endif
	} else if ( strcmp(argv[i], "--cxxflags") == 0 ) {
			cout << " -I" << Vision_HEADERS_PATH ;
		 	cout << " -I" << Vision_EIGEN3_HEADERS_PATH ;	
			#if ( Vision_IMAGEMAGICK == TRUE )
				cout << " -I" << Vision_IMAGEMAGICK_HEADERS_PATH ;
		        #endif	
	} else if ( strcmp(argv[i], "--ldflags") == 0 ) {
			cout << " -L" << Vision_LIBS_PATH ;
	} else {
			display_help() ;

	}

	cout << endl ;

	return 0 ;
}
