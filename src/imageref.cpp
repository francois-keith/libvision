#include <visionlib/imageref.h>


ImageRef &ImageRef::operator=(const ImageRef& source) {
	x = source.x ;
	y = source.y ;
	return *this ;
}


ImageRef &ImageRef::operator+=(const ImageRef& right) {
	x += right.x;
	y += right.y;
        return *this;


}


ImageRef &ImageRef::operator-=(const ImageRef& right) {
	x -= right.x;
	y -= right.y;
        return *this;


}


ImageRef operator+(const ImageRef &c1, const ImageRef &c2) {
    ImageRef result = c1;
    return result += c2;
}

ImageRef operator-(const ImageRef &c1, const ImageRef &c2) {
    ImageRef result = c1;
    return result -= c2;
}

bool operator==( const ImageRef &c1, const ImageRef &c2) {
	return ( c1.x == c2.x ) && (c1.y == c2.y ) ;
}

bool operator!=( const ImageRef &c1, const ImageRef &c2) {
	return ( c1.x != c2.x ) || (c1.y != c2.y ) ;
}



int ImageRef::area() {
	return x*y ;
}
