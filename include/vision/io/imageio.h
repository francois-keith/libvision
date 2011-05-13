#ifndef VL_IMAGEIO_H
#define VL_IMAGEIO_H

#include <vision/vision.h>
#include <vision/image/image.h>
#include <vision/image/color.h>

#if (Vision_IMAGEMAGICK == True ) 

#include <Magick++.h>

namespace vision {
	

	template<typename Pixel, int ColorCoding> 
	void save_mono ( std::string filename, Image<Pixel>* img ) {
 		Magick::Image image( Magick::Geometry( img->width, img->height), "black" ) ;
		for (int i=0; i<img->width; i++ )
		for (int j=0; j<img->height; j++ ) 
     			image.pixelColor(i,j, Magick::ColorGray( 
				pixel2mono<Pixel,ColorCoding>( (*img)[j][i] ) ) ); 
        	image.write( filename );
	}
	
	template<typename Pixel, int ColorCoding> 
	Image<Pixel>* load_mono ( std::string filename ) {
		Magick::Image src( filename ) ;
		int width = src.size().width() ;
		int height = src.size().height() ;
		double Value ;
		Image<Pixel> *img = new Image<Pixel>(width,height) ;
		src.quantizeColorSpace( Magick::GRAYColorspace ); 
		src.quantizeColors( 256 ); 
		src.quantize( );
		for ( int i=0; i<img->width; i++ )
		for ( int j=0; j<img->height; j++ ) {
			Magick::Quantum R,G,B ;
			Magick::Color C = src.pixelColor(i,j) ;
			R = C.redQuantum() ;
			G = C.greenQuantum() ;
			B = C.blueQuantum() ;
			Value =  R / (double) QuantumRange ;
			Value += G / (double) QuantumRange ;
			Value += B / (double) QuantumRange ;
			Value /= 3.0 ;
			(*img)[j][i] = mono2pixel<Pixel,ColorCoding>( Value ) ;
		}
		return img ;
	}

	template<typename Pixel, int ColorCoding>
	void save_color ( std::string filename, Image<Pixel>* img ) {
		Magick::Image image( Magick::Geometry( img->width, img->height), "black" ) ;
		double R,G,B ;
		for (int i=0; i<img->width; i++ )
		for (int j=0; j<img->height; j++ ) {
			pixel2rgb<Pixel, ColorCoding>((*img)[j][i], R, G, B ) ; 
     			image.pixelColor(i,j, Magick::ColorRGB(R,G,B) ) ; 
		}
		image.write( filename );
	}

	template<typename Pixel, int ColorCoding>
	Image<Pixel>* load_color ( std::string filename ) {
		Magick::Image src( filename ) ;
		int width = src.size().width() ;
		int height = src.size().height() ;
		Image<Pixel> *img = new Image<Pixel>(width,height) ;
		for ( int i=0; i<img->width; i++ )
		for ( int j=0; j<img->height; j++ ) {
			Magick::Color C = src.pixelColor(i,j) ;
			double R = C.redQuantum()   / (double) QuantumRange  ;
			double G = C.greenQuantum() / (double) QuantumRange  ;
			double B = C.blueQuantum()  / (double) QuantumRange  ;
			(*img)[j][i] = rgb2pixel<Pixel,ColorCoding>(R,G,B) ;
		}
		return img ;

	}


}

#endif






#endif
