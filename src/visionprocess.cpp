#include <visionlib/visionprocess.h>

using namespace std ;

VisionProcess::VisionProcess( VisionServer* srv, string name ) {
	process_name = name ;
	vision_server = srv ;
}

VisionProcess::~VisionProcess() {

}

int push_image ( Image<unsigned char> *img, int numcam ) {

}

Image<unsigned char>* dequeue_image( int i ) {

}

void enqueue_image( Image<unsigned char>* img, int i ) {

}

void register_to_cam ( int i ) {

}

