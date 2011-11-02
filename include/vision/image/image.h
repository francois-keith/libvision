#ifndef VL_IMAGE_H
#define VL_IMAGE_H

#include <cstring>
#include <fstream>
#include <iostream>

#include <vision/image/imageref.h>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/binary_object.hpp>

namespace vision {

#define DEPTH		-1
#define TEMPERATURE	-2
#define DISPARITY	-3
#define MONO    	-4
#define RGB		-5
#define RGBA		-6
#define HSV		-7
#define YUV		-8

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

template < typename Pix, int ColorSpace > 
class Image
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

  Image () : width(0), height(0), pixels(0), size(0,0), pixel_size(0), data_size(0), raw_data(0) {}
  Image (ImageRef size) ;
  Image (const Image<Pix,ColorSpace> &img) ;
  Image (unsigned int width, unsigned int height) ;
  
  ~Image ();

  Pix* operator[](unsigned int line) const;
  Pix& operator()(ImageRef coord) const;
  Pix& operator()(unsigned int x, unsigned int y ) const;

  Image<Pix,ColorSpace>* clone() ;
  void copy( Image<Pix,ColorSpace> *img ) ;
  void copy( const Image<Pix,ColorSpace> & img ) ;

private:

  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & width;
    ar & height;
    ar & pixels;
    ar & size;
    ar & pixel_size;
    /* This is needed if you load an image with an empty image or an image with a different resolution*/
    if(!raw_data || pixels*pixel_size !=  data_size) 
    { 
      delete raw_data;
      raw_data = new Pix[pixels]; 
    } 
    ar & data_size;
    ar & boost::serialization::make_binary_object(raw_data, data_size);
  }

};

#include "image.hpp"

}

#endif
