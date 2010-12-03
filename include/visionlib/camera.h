#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <vector>

#include <stdint.h>

#include <visionlib/image.h>
#include <visionlib/matrice.h>

using namespace std ;


template< typename T >
class GenericCamera {

	public :

		GenericCamera( uint64_t gid ) ;
		uint64_t get_gid() ;
	
		ImageRef get_size() ;					// returns frame size
		int get_width()  { return size.x ; }
		int get_height() { return size.y ; }
		
		bool is_active() { return active ; }
		void set_active() { active = true ; }
		void set_inactive() { active = false ; }

		virtual bool start_cam() = 0 ;				// Initialisation / starts frame grabbing
		virtual void grab_frame ( Image<T> * ) = 0 ;		// Fills the given image
		virtual bool stop_cam() = 0 ;

	protected :

		void set_size( int x, int y ) ;

	private :

		uint64_t gid ;
		ImageRef size ;

		bool active ;

} ;



template< typename T >
class CalibratedCamera : public GenericCamera<T> 
{

	public :
		
		CalibratedCamera( uint64_t id ) ;


		virtual vector<double> get_parameters () = 0 ;				// pretty self explanatory. What is inside the vector	
		virtual void  set_parameters ( vector<double> ) = 0 ; 			//	will depend on the underlying camera model

		virtual double calibrate () = 0 ;					// FIXME have to decide wich arguments to give to this function

		virtual ImageRef  project ( Matrice ) = 0 ;				// projects a 3D point

		virtual void undistord ( Image<T>* input, Image<T>* output ) = 0 ;	// undistord an image

		

} ;


#include <visionlib/camera.hpp>


#endif
