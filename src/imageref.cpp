#include <vision/image/imageref.h>

namespace vision {

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


ImageRef &ImageRef::operator+=(const int& right) {
	x += right;
	y += right;
        return *this;
}

ImageRef &ImageRef::operator-=(const int& right) {
	x -= right;
	y -= right;
        return *this;
}

ImageRef &ImageRef::operator*=(const int& right) {
	x *= right;
	y *= right;
        return *this;
}

ImageRef &ImageRef::operator/=(const int& right) {
	x /= right;
	y /= right;
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

ImageRef operator+(const ImageRef &c1, const int &a ) {
	ImageRef result = c1 ;
	return result += a ;
}

ImageRef operator-(const ImageRef &c1, const int &a ) {
	ImageRef result = c1 ;
	return result -= a ;
}


ImageRef operator*(const ImageRef &c1, const int &a ) {
	ImageRef result = c1 ;
	return result *= a ;
}


ImageRef operator/(const ImageRef &c1, const int &a ) {
	ImageRef result = c1 ;
	return result /= a ;
}


bool operator==( const ImageRef &c1, const ImageRef &c2) {
	return ( c1.x == c2.x ) && (c1.y == c2.y ) ;
}


bool operator!=( const ImageRef &c1, const ImageRef &c2) {
	return ( c1.x != c2.x ) || (c1.y != c2.y ) ;
}

std::ostream & operator<<(std::ostream & out, const ImageRef & ref_in)
{
    out << ref_in.x << " , " << ref_in.y; 
    return out;
}

std::istream & operator>>(std::istream & in, ImageRef & ref_out)
{
    char tmp = 0;
    in >> ref_out.x;
    do 
    {
        in >> tmp;
    } while(in && tmp != ',');
    in >> ref_out.y;
}

int ImageRef::area() {
	return x*y ;
}

int ImageRef::mag_squared() {
	return x*x+y*y ;
}

}
