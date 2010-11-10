#ifndef VISIONLIB_IMAGE_H
#define VISIONLIB_IMAGE_H

#include <stdlib.h>

class ImageRef
{
public:
  unsigned int x;
  unsigned int y;
};




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



#endif
