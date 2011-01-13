#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <vector>

#include <stdint.h>

#include <visionlib/image.h>

using namespace std ;


template< typename T >
class GenericCamera {

	public :

		GenericCamera( uint64_t gid ) ;
		virtual ~GenericCamera();
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


#include <visionlib/camera.hpp>


#endif
