#ifndef ROBOTVISION_VISIONPROCESS_H
#define ROBOTVISION_VISIONPROCESS_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include <visionlib/image.h>
#include <visionlib/imagebuffer.h>
#include <visionlib/camera.h>

using namespace std ;

class VisionProcess ;
class VisionServer  ;

class VisionServer {
	public:
		virtual VisionProcess* get_process_by_name (string) = 0 ;			// retrieves a pointer to one of the processes run by the server
		virtual GenericCamera<unsigned char>* get_camera ( int i )  = 0 ;		// retrieves a pointer to the camera number ith
		virtual int get_num_cameras() = 0 ;						// retrieves the number of cameras managed by the server

		virtual void register_to_cam ( VisionProcess*, int cam, int ringbuffer ) = 0 ;  // registers a process to a cam
		virtual void stop() = 0 ;							// stops the server main loop
		virtual string get_plugin_path() = 0 ;						// returns the path to plugins conf directories
};

class VisionProcess {


	public:

	VisionProcess ( VisionServer* srv, string name) ;
	~VisionProcess() ;

	int push_image( Image<unsigned char>*, int numcam ) ;		// Called by the VisionServer. Pushes the image from Cam numcam to the corresponding ringbuffer. 
	
	string get_name() ;						// Returns a string with the name of the process 

	virtual bool pre_fct()  = 0 ;					// Will be called first by VisionServer. Put your initialisation stuff here.
	virtual bool post_fct() = 0 ;					// Will be called by VisionServer before Terminaison. Close/Save all you need here.
	virtual void* main_fct() = 0 ;					// Will be called by the VisionServer. Thread main function

	protected:

	Image<unsigned char>* dequeue_image ( int i ) ;			// Pulls a frame from the ring buffer for processing. Will not return until it gets one
	void   enqueue_image ( Image<unsigned char>* img, int i ) ;	// Each frame must be sent back to the ring buffer once you're done with it.

	void register_to_cam (int cam ) ;				// Registers to receive frames from cam NumCam. Next RingBuffer is affected to this cam.
	
	VisionServer* vision_server ;					// Pointer to the VisionServer

	
	ofstream 	err   ;						// file for error logging
	ofstream	out   ;						// file for output logging

	private:

	string process_name ;						// Name of the process
	string path_config ;						// Directory containing the config files for this plugin

	vector<ImageBuffer*> buffers ;					// A vector with the ringbuffers we've registered to.

} ;


typedef VisionProcess* create_t(VisionServer*);
typedef void destroy_t(VisionProcess*);

#endif
