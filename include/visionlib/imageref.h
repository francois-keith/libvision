#ifndef VISIONLIB_IMAGEREF_H
#define VISIONLIB_IMAGEREF_H

#include <stdlib.h>

class ImageRef
{

  friend ImageRef operator+(const ImageRef &, const ImageRef &);
  friend ImageRef operator-(const ImageRef &, const ImageRef &);

  friend bool operator==(const ImageRef &, const ImageRef &);
  friend bool operator!=(const ImageRef &, const ImageRef &);

  friend ImageRef operator+(const ImageRef &, const int & ) ;
  friend ImageRef operator-(const ImageRef &, const int & ) ;
  friend ImageRef operator*(const ImageRef &, const int & ) ;
  friend ImageRef operator/(const ImageRef &, const int & ) ;

public:

  unsigned int x;
  unsigned int y;

  ImageRef(int X, int Y ) { x = X;  y = Y; }
  ImageRef() { x=0; y=0; }

  ImageRef &operator=(const ImageRef &);
  ImageRef &operator+=(const ImageRef& ) ;
  ImageRef &operator-=(const ImageRef& ) ;
  ImageRef &operator+=(const int& ) ;
  ImageRef &operator-=(const int& ) ;
  ImageRef &operator*=(const int& ) ;
  ImageRef &operator/=(const int& ) ;

  int mag_squared() ;

  int area() ;

};


#endif
