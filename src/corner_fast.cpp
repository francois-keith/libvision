#include <vision/corners/fast.h>

#include "fast/fast.h"


namespace vision { 

void fast9_detect ( Image<unsigned char>* img , double b, vector<ImageRef> *ret ) {

	xy* result ;
	int nb ;
	result = fast9_detect_nonmax ( (const byte*) img->raw_data, img->width, img->height, img->width, b, &nb ) ; 
	for (int i=0; i<nb; i++)
		ret->push_back ( ImageRef(result[i].x, result[i].y) ) ;
	free (result) ;
}

}
