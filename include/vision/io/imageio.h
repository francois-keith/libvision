#ifndef VL_IMAGEIO_H
#define VL_IMAGEIO_H

#include <vision/config.h>
#include <vision/image/image.h>
#include <vision/io/pixelcoding.h>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

namespace vision
{

template<typename Pix, int ColorSpace>
void serialize(const std::string & to_file, const Image<Pix, ColorSpace> & img)
{
    std::ofstream ofs(to_file.c_str(), std::ios::binary);
    boost::archive::binary_oarchive oa(ofs);
    oa << img;
}

template<typename Pix, int ColorSpace>
void deserialize(const std::string & from_file, Image<Pix, ColorSpace> & img)
{
    std::ifstream ifs(from_file.c_str(), std::ios::binary);
    boost::archive::binary_iarchive ia(ifs);
    ia >> img;
}

} // namespace vision

#if (Vision_IMAGEMAGICK == 1 ) 

#include <Magick++.h>


namespace vision {
	

	template<typename Pixel, int ColorSpace> 
	void save_mono ( std::string filename, Image<Pixel,ColorSpace>* img ) {
 		Magick::Image image( Magick::Geometry( img->width, img->height), "black" ) ;
		for (unsigned int i=0; i<img->width; i++ )
		for (unsigned int j=0; j<img->height; j++ ) 
     			image.pixelColor(i,j, Magick::ColorGray( 
				pixel2mono<Pixel,ColorSpace>( (*img)[j][i] ) ) ); 
        	image.write( filename );
	}
	
	template<typename Pixel, int ColorSpace> 
	Image<Pixel,ColorSpace>* load_mono ( std::string filename ) {
		Magick::Image src( filename ) ;
		int width = src.size().width() ;
		int height = src.size().height() ;
		double Value ;
		Image<Pixel,ColorSpace> *img = new Image<Pixel,ColorSpace>(width,height) ;
		src.quantizeColorSpace( Magick::GRAYColorspace ); 
		src.quantizeColors( 256 ); 
		src.quantize( );
		for ( unsigned int i=0; i<img->width; i++ )
		for ( unsigned int j=0; j<img->height; j++ ) {
			Magick::Quantum R,G,B ;
			Magick::Color C = src.pixelColor(i,j) ;
			R = C.redQuantum() ;
			G = C.greenQuantum() ;
			B = C.blueQuantum() ;
			Value =  Magick::Color::scaleQuantumToDouble(R) ;
			Value +=  Magick::Color::scaleQuantumToDouble(G) ;
			Value += Magick::Color::scaleQuantumToDouble(B)  ;
			Value /= 3.0 ;
			(*img)[j][i] = mono2pixel<Pixel,ColorSpace>( Value ) ;
		}
		return img ;
	}

	template<typename Pixel, int ColorSpace>
	void save_color ( std::string filename, Image<Pixel,ColorSpace>* img ) {
		Magick::Image image( Magick::Geometry( img->width, img->height), "black" ) ;
		double R,G,B ;
		for (unsigned int i=0; i<img->width; i++ )
		for (unsigned int j=0; j<img->height; j++ ) {
			pixel2rgb<Pixel, ColorSpace>((*img)[j][i], R, G, B ) ; 
     			image.pixelColor(i,j, Magick::ColorRGB(R,G,B) ) ; 
		}
		image.write( filename );
	}

	template<typename Pixel, int ColorSpace>
	Image<Pixel,ColorSpace>* load_color ( std::string filename ) {
		Magick::Image src( filename ) ;
		int width = src.size().width() ;
		int height = src.size().height() ;
		Image<Pixel,ColorSpace> *img = new Image<Pixel,ColorSpace>(width,height) ;
		for ( unsigned int i=0; i<img->width; i++ )
		for ( unsigned int j=0; j<img->height; j++ ) {
			Magick::Color C = src.pixelColor(i,j) ;
			double R = Magick::Color::scaleQuantumToDouble( C.redQuantum() )    ;
			double G = Magick::Color::scaleQuantumToDouble( C.greenQuantum() ) ;
			double B = Magick::Color::scaleQuantumToDouble( C.blueQuantum() ) ;
			(*img)[j][i] = rgb2pixel<Pixel,ColorSpace>(R,G,B) ;
		}
		return img ;

	}


}

#else

#pragma message "[Warning] You are including imageio without ImageMagick, using save/load_mono/color will result in exceptions"
namespace vision {
	

	template<typename Pixel, int ColorSpace> 
	void save_mono ( std::string filename, Image<Pixel,ColorSpace>* img ) {
        std::throw(std::string("[Error] Calling save_mono without ImageMagick++ support"));
	}
	
	template<typename Pixel, int ColorSpace> 
	Image<Pixel,ColorSpace>* load_mono ( std::string filename ) {
        std::throw(std::string("[Error] Calling load_mono without ImageMagick++ support"));
	}

	template<typename Pixel, int ColorSpace>
	void save_color ( std::string filename, Image<Pixel,ColorSpace>* img ) {
        std::throw(std::string("[Error] Calling save_color without ImageMagick++ support"));
	}

	template<typename Pixel, int ColorSpace>
	Image<Pixel,ColorSpace>* load_color ( std::string filename ) {
        std::throw(std::string("[Error] Calling load_color without ImageMagick++ support"));
	}


}


#endif




#endif
