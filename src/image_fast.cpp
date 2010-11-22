#include "fast/fast.h"
#include <visionlib/corners/fast.h>


vector<ImageRef> fast9_detect_nonmax ( Image<unsigned char>* img , double b ) {

	xy* result ;
	vector<ImageRef> ret ;
	int nb ;
	result = fast9_detect_nonmax ( (const byte*) img->get_raw_data(), img->get_width(), img->get_height(), img->get_width(), b, &nb ) ; 
	for (int i=0; i<nb; i++)
		ret.push_back ( ImageRef(result[i].x, result[i].y) ) ;
	free (result) ;
	return ret ;
}


vector<ImageRef> fast10_detect_nonmax ( Image<unsigned char>* img ) {

}


vector<ImageRef> fast11_detect_nonmax ( Image<unsigned char>* img ) {

}


vector<ImageRef> fast12_detect_nonmax ( Image<unsigned char>* img ) {

}


