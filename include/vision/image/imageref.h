#ifndef VL_IMAGEREF_H
#define VL_IMAGEREF_H

#include <stdlib.h>

#include <boost/serialization/serialization.hpp>

namespace vision {

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

  friend std::ostream& operator << (std::ostream& out, const ImageRef& ref_in); 
  friend std::istream& operator >> (std::istream& in, ImageRef& ref_out);

public:

  int x;
  int y;

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

private:
  
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & x;
    ar & y;
  }

};


}

#endif
