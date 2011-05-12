#ifndef VL_IMAGEIO_H
#define VL_IMAGEIO_H

#include <vision/vision.h>

#if Vision_ImageMagick
#include <Magick++.h>
#endif

namespace vision {
	
	#if Vision_IMAGEMAGICK

	template<typename Pixel> 
	void save_mono ( std::string filename, Image<Pixel>* img ) {
		
	}
	
	template<typename Pixel> 
	void load_mono ( std::string filename, Image<Pixel>* img ) {

	}

	template<typename Pixel>
	void save_rgb ( std::string filename, Image<Pixel>* img ) {

	}

	template<typename Pixel>
	void load_rgb ( std::string filename, Image<Pixel>* img ) {

	}



	#endif




}

#endif
