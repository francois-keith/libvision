#ifndef VISIONLIB_IMAGEREF_H
#define VISIONLIB_IMAGEREF_H

#include <stdlib.h>

class ImageRef
{

  friend ImageRef operator+(const ImageRef &, const ImageRef &);
  friend ImageRef operator-(const ImageRef &, const ImageRef &);
  friend bool operator==(const ImageRef &, const ImageRef &);
  friend bool operator!=(const ImageRef &, const ImageRef &);
public:

  unsigned int x;
  unsigned int y;

  ImageRef(int X, int Y ) { x = X;  y = Y; }
  ImageRef() { x=0; y=0; }

  ImageRef &operator=(const ImageRef &);
  ImageRef &operator+=(const ImageRef& ) ;
  ImageRef &operator-=(const ImageRef& ) ;

  int area() ;

};


#endif
