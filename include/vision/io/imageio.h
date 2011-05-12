#ifndef VL_IMAGEIO_H
#define VL_IMAGEIO_H

#include <vision/image/image.h>
#include <vision/image/color.h>


#if Vision_ImageMagick
#include <Magick++.h>
#endif

namespace vision {
	
	#if Vision_IMAGEMAGICK

	template<typename Pixel, const char* Coding> 
	void save_mono ( std::string filename, Image<Pixel>* img ) {
 		Magick::Image image( img->width, img->height );				// FIXME
		image.type( Magick::GrayscaleType );
		for (int i=0; i<img->width; i++ )
			for (int j=0; j<img->height; j++ ) 
     				image.pixelColor(i,j, Magick::ColorGrey( pixel2mono<Pixel,Coding>( img->data[j][i] ) ) ); 
        	image.write( filename );
	}
	
	template<typename Pixel> 
	void load_mono ( std::string filename, Image<Pixel>* img ) {

	}

	template<typename Pixel>
	void save_color ( std::string filename, Image<Pixel>* img ) {

	}

	template<typename Pixel>
	void load_color ( std::string filename, Image<Pixel>* img ) {

	}



	#endif




}

#endif
