#ifndef VISIONLIB_IMAGE_H
#define VISIONLIB_IMAGE_H

#include <stdlib.h>
#include <visionlib/imageref.h>

#include <iostream>

template < typename Pix > class Image
{

public:

  Image ( ImageRef imgref ) ;
  Image ( int width, int height);
  ~Image ();

  unsigned int get_width ()
  {
    return width;
  }
  unsigned int get_height ()
  {
    return height;
  }
  ImageRef get_size ()
  {
    return ImageRef (width, height);
  }

  Pix* get_raw_data()
  {
   return data ;
  }

  Pix& operator[] ( ImageRef coord )
  {
        return data[coord.x + coord.y * width] ;
  }

  Pix* scale() ;


private:

  int width;
  int height;
  int num_pixels;	// width * height
  Pix *data;


};



template<typename Pix> 
Image<Pix>::Image (int w, int h)
{
  width = w;
  height = h;
  num_pixels = w * h;
  data = (Pix *) malloc ( num_pixels * sizeof (Pix) );
  if (data == NULL)
    throw "malloc error" ;

}

template<typename Pix>
Image<Pix>::Image( ImageRef ir ) {
	 width = ir.x;
	 height = ir.y;
	 num_pixels = ir.x * ir.y;
	 data = (Pix *) malloc ( num_pixels * sizeof (Pix) );
	 if (data == NULL)
		throw "malloc error" ;
}

template < typename Pix >
Image<Pix>::~Image ()
{
  free (data);
}

template< typename Pix >							//FIXME (beurk)
Pix* Image<Pix>::scale() {
	Pix* buff ;
	buff = (Pix*) malloc ( num_pixels / 16 * sizeof(Pix) ) ;
	for (int i=0; i<width; i+=4 )
	for (int j=0; j<height; j+=4 ) {
		int acc =0 ;
		for (int k=0; k<4; k++ )
		for (int l=0; l<4; l++ )
			acc+= (int) data[i+k+(j+l)*width] ;
	
		acc /= 16 ;

		buff[i/4+width/4 * j/4] = (Pix) acc ;
	}

	return buff ;
}
#endif
