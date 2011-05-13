#ifndef VL_COLOR_H
#define VL_COLOR_H


#define MONO    -1
#define RGB	-2


template< typename Pix, int ColorCoding >
double pixel2mono ( Pix value ) 
{
	return (double) value ;

}

template< typename Pix, int ColorCoding >
Pix mono2pixel ( double value ) 
{
	return (Pix) value ;
}


template< typename Pix, int ColorCoding >
void pixel2rgb ( Pix value, double &red, double &green, double &blue ) 
{
	red   =  (( value | 0xFF0000 ) >> 16 ) / 255.0;
	green =  (( value | 0x00FF00 ) >> 8 )  / 255.0;
	blue  =  (( value | 0x0000FF )) / 255.0 ;

}



// -----------------------------------------------------------------


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
	( unsigned char value, double &red, double &green, double &blue ) {

	red = value / 255.0 ;
	blue = red ;
	green = red ;
}


#endif
