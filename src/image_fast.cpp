#include "vision/corner_fast.h"
#include "fast/fast.h"


using namespace vision ;

void fast9_detect ( Image<unsigned char>* img , double b, vector<ImageRef> *ret ) {

	xy* result ;
	int nb ;
	result = fast9_detect_nonmax ( (const byte*) img->get_raw_data(), img->get_width(), img->get_height(), img->get_width(), b, &nb ) ; 
	for (int i=0; i<nb; i++)
		ret->push_back ( ImageRef(result[i].x, result[i].y) ) ;
	free (result) ;
}


