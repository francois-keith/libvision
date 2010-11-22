#ifndef VL_FAST_H
#define VL_FAST_H

#include <vector>

#include <visionlib/image.h>

using namespace std ;

vector<ImageRef> fast9_detect_nonmax  ( Image<unsigned char>* img, double b );
vector<ImageRef> fast10_detect_nonmax ( Image<unsigned char>* img, double b );
vector<ImageRef> fast11_detect_nonmax ( Image<unsigned char>* img, double b );
vector<ImageRef> fast12_detect_nonmax ( Image<unsigned char>* img, double b );




#endif
