#ifndef VL_PINHOLECAM_H
#define VL_PINHOLECAM_H

#include <iostream>
#include <Eigen/Dense>
#include <vision/image/imageref.h>


namespace vision {

class PinholeCam {

	public:

		PinholeCam() ;
		PinholeCam( double cx, double cy, double fx, double fy, double s ) ;	

		Eigen::Vector2d Project   ( Eigen::Vector3d ) ;
		Eigen::Vector3d UnProject ( Eigen::Vector2d ) ;

		Eigen::Vector2d get_f() ;
		Eigen::Vector2d get_c() ;

		PinholeCam& operator= (const PinholeCam &other) ;
		
		friend std::ostream &operator >> ( std::ostream &os_o, PinholeCam &ref );
		friend std::istream &operator << ( std::istream &is_o, PinholeCam &ref );

	public:

		Eigen::Matrix<double, 3, 3>			K ;		
		Eigen::Matrix<double, 1, Eigen::Dynamic >	D ;
};

}

#endif
