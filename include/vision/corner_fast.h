#ifndef VL_FAST_H
#define VL_FAST_H

#include <vector>

#include <vision/image.h>

using namespace std ;

namespace vision {

void fast9_detect  ( Image<unsigned char>* img, double b, vector<ImageRef> *ret  );

// vector<ImageRef> fast10_detect_nonmax ( Image<unsigned char>* img, double b );
// vector<ImageRef> fast11_detect_nonmax ( Image<unsigned char>* img, double b );
// vector<ImageRef> fast12_detect_nonmax ( Image<unsigned char>* img, double b );

}


#endif
