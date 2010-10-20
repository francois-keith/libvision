#ifndef ROBOTVISION_VISIONPROCESS_H
#define ROBOTVISION_VISIONPROCESS_H

#include <vector>
#include <string>

#include <visionlib/image.h>
#include <visionlib/imagebuffer.h>

using namespace std ;

class VisionProcess ;
class VisionServer  ;

class VisionServer {
	public:
		virtual VisionProcess* get_process_by_name (string) = 0 ;			// retrieves a pointer to one of the processes run by the server
		virtual void register_to_cam ( VisionProcess*, int cam, int ringbuffer ) = 0 ;  // registers a process to a cam
};

class VisionProcess {


	public:

	VisionProcess ( VisionServer* srv) ;
	~VisionProcess() ;

	int push_image( Image<unsigned char>*, int numcam ) ;		// Called by the VisionServer. Pushes the image from Cam numcam to the corresponding ringbuffer. 
	
	virtual string get_name() = 0 ;					// Must return a string with the name of the process (Called by VisionServ )
	
	virtual bool pre_fct()  = 0 ;					// Will be called first by VisionServer. Put your initialisation stuff here.
	virtual bool post_fct() = 0 ;					// Will be called by VisionServer before Terminaison. Close/Save all you need here.
	virtual bool main_fct() = 0 ;					// Will be called by the VisionServer. Thread main function

	protected:

	Image<unsigned char>* dequeue_image ( int i ) ;			// Pulls a frame from the ring buffer for processing. Will not return until it gets one
	void   enqueue_image ( Image<unsigned char>* img, int i ) ;	// Each frame must be sent back to the ring buffer once you're done with it.

	void register_to_cam (int cam ) ;				// Registers to receive frames from cam NumCam. Next RingBuffer is affected to this cam.
	
	VisionServer* vision_server ;					// Pointer to the VisionServer

	private:

	string process_name ;						// Name of the process

	vector<ImageBuffer> buffers ;					// A vector with the ringbuffers we've registered to.

} ;

typedef VisionProcess* create_t(VisionServer*);
typedef void destroy_t(VisionProcess*);

#endif
