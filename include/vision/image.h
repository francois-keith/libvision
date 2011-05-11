#ifndef VL_IMAGE_H
#define VL_IMAGE_H

#include <cstring>
#include <iostream>

#include <vision/imageref.h>

namespace vision {


// *************************************************
// ***
// *** Class: Image<Pix>
// ***
// *************************************************


// This Image class is inspired from the libCVD
//
// The template parameter is the pixel type, so you can use
// it with any kind of data ... 
//
// All members ( width, height, etc ) are declared public ... which is
// probably not a good idea, but makes things so easier when using it !
// Read them, use them, but don't modify them in your code, or you'll 
// segfault ! You've been warned :)


template < typename Pix > class Image
{

public:

  unsigned int width ;		// width of the image  ( in pixels )
  unsigned int height ;		// height of the image ( in pixels )
  unsigned int pixels ;		// total number of pixels ( width * height ) 
  
  ImageRef size ;	// size of the image ( width, height )

  size_t pixel_size ;   // size of a pixel in bytes
  size_t data_size ;    // size of the image in bytes ( width*height*pixel_size )

  Pix* raw_data ;	// Image data, in ROW order.

public:

  Image ( ImageRef size ) ;
  Image ( const Image<Pix> &img ) ;
  Image ( unsigned int width, unsigned int height) ;
  
  ~Image ();


  Pix& operator[] ( ImageRef coord ) ;
  Pix* operator[] ( unsigned int line ) ;

  Image<Pix>* clone() ;

};


template<typename Pix>
Image<Pix>::Image( ImageRef ir ) 
{
  width = ir.x;
  height = ir.y;
  pixels = ir.x*ir.y ;
  size = ImageRef(ir.x,ir.y) ;
  pixel_size = sizeof ( Pix ) ;
  data_size = pixels * pixel_size ;
  raw_data = new Pix[pixels];
  if (raw_data == NULL)
    throw "new[] error" ;
}

template<typename Pix>
Image<Pix>::Image( const Image<Pix> &img ) 
{
  width = img.width ;
  height = img.height ;
  pixels = img.pixels ;
  size = img.size ;
  pixel_size = img.pixel_size ;
  data_size = img.data_size ;
  raw_data = new Pix[pixels];
  if (raw_data == NULL)
    throw "new[] error" ;
  std::memcpy ( img.raw_data, raw_data, data_size ) ;
}

template<typename Pix> 
Image<Pix>::Image (unsigned int w, unsigned int h)
{
  width = w;
  height = h;
  pixels = w * h;
  size = ImageRef(w,h) ;
  pixel_size = sizeof ( Pix ) ;
  data_size = pixels * pixel_size ;
  raw_data = new Pix[pixels];
  if (raw_data == NULL)
    throw "new[] error" ;
}

template<typename Pix>
Image<Pix>::~Image ()
{
	delete[] raw_data;
}

template <typename Pix>
Pix& Image<Pix>::operator[] ( ImageRef coord )
{
	return raw_data[coord.x+coord.y*width] ;
}

template <typename Pix>
Pix* Image<Pix>::operator[] ( unsigned int line ) {
	return &(raw_data[line*width] ) ;
}

template<typename Pix >
Image<Pix>* Image<Pix>::clone() {
	Image<Pix>* img ;
	img = new Image<Pix>(width,height) ;
	std::memcpy ( img->raw_data, raw_data, data_size ) ;
	return img ;
}


}

#endif
