#ifndef VL_SCALE_H
#define VL_SCALE_H

#include <vision/image.h>

namespace vision {

template< typename Pix >							
Image<Pix>* scale( Image<Pix>* src, unsigned int scale_factor) {
	Image<Pix>* img = new Image<Pix>(src->width/scale_factor,src->height/scale_factor) ;
	unsigned int nb = scale_factor * scale_factor ;
	for (int i=0; i<img->width; i++ ) 
	for (int j=0; j<img->height; j++ ) {
		Pix acc =0 ;
		for (int k=i*scale_factor; k<(i+1)*scale_factor; k++ ) 
		for (int l=j*scale_factor; l<(j+1)*scale_factor; l++ ) {
			acc += src->raw_data[k+l*src->width] ;
		}
		acc /= nb ;
		img->raw_data[i+j*img->width] = acc ;
	}
	return img ;
}



template<>							
Image<unsigned char>* scale( Image<unsigned char>* src, unsigned int scale_factor) ;




}
#endif

