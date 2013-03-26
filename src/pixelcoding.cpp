
#include <vision/image/image.h>
#include <vision/io/pixelcoding.h>

namespace vision {

template<>
double pixel2mono<unsigned char, MONO>( unsigned char value )
{
	return (double) ( value / 255.0 ) ;
}

template<>
unsigned char mono2pixel<unsigned char, MONO>( double value ) 
{
	return (unsigned char) ( 255 * value ) ;
}

template<>
void pixel2rgb<unsigned char, MONO>
	( unsigned char value, double &red, double &green, double &blue, double & alpha ) {

	red = value / 255.0 ;
	blue = red ;
	green = red ;
    alpha = 0;
}

template<>
unsigned char rgb2pixel<unsigned char, MONO> ( double R, double G, double B ) {
	return (unsigned char) ((( R + G + B ) / 3.0 ) * 255.0 )  ;
}


// -----------------------------------------------------------------

template<>
double pixel2mono<unsigned int, RGB>( unsigned int value ) 
{
	unsigned char* tab = (unsigned char*)  &value ;
	double red   =  tab[0] / 255.0;
	double green =  tab[1] / 255.0;
	double blue  =  tab[2] / 255.0 ;
	return (red + green + blue) / 3.0 ;
}


template<>
void pixel2rgb<unsigned int, RGB>(unsigned int value, double &R, double &G, double &B, double &A) 
{
	unsigned char* tab = (unsigned char*)  &value ;
	R  =  tab[0] / 255.0;
	G  =  tab[1] / 255.0;
	B  =  tab[2] / 255.0;
    A  =  tab[3] / 255.0;
}


template<>
unsigned int rgb2pixel<unsigned int, RGB>( double R, double G, double B ) 
{
	unsigned int value ;
	unsigned char* tab = (unsigned char*) &value ;
	tab[0] = (unsigned char) ( R * 255.0 ) ;
	tab[1] = (unsigned char) ( G * 255.0 ) ;
	tab[2] = (unsigned char) ( B * 255.0 ) ;
	return value ;
}


}
