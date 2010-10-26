#include <visionlib/imagebuffer.h>
#include <visionlib/visionprocess.h>
#include <iostream>

using namespace std ;


VisionProcess::VisionProcess( VisionServer* srv ) {
	vision_server = srv ;
}

VisionProcess::~VisionProcess() {
	
	for ( int i=0; i< buffers.size(); i++ )
		delete ( buffers[i] ) ;
}

int VisionProcess::push_image ( Image<unsigned char> *img, int numcam ) {

}

Image<unsigned char>* VisionProcess::dequeue_image( int i ) {

}

void VisionProcess::enqueue_image( Image<unsigned char>* img, int i ) {
	buffers[i]->push ( img ) ;
}

void VisionProcess::register_to_cam ( int i ) {

	int nbuff ;
	ImageBuffer* rbuff ;
	ImageRef size ;

	size = vision_server->get_camera(i)->get_size() ;

	rbuff = new ImageBuffer( size ,5) ;
	buffers.push_back ( rbuff ) ;

	nbuff = buffers.size() - 1 ;

	vision_server->register_to_cam ( this, i, nbuff ) ; 

}

