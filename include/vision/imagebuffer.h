#ifndef ROBOTVISION_IMAGEBUFFER_H
#define ROBOTVISION_IMAGEBUFFER_H

#include <vector>
#include <pthread.h>
#include <vision/image.h>

using namespace std ;

class ImageBuffer {

	private:

	vector<Image<unsigned char>*> frames ;
	vector<Image<unsigned char>*> trash  ;
	

	pthread_mutex_t mutex ; 

	public:

	ImageBuffer( ImageRef image_size, int N ) ;	    	    		    // Allocates a buffer of N images (specified size)
	~ImageBuffer() ;

	Image<unsigned char>* dequeue () ;					    // Removes next frame from the buffer and returns it. Blocking call.
	void enqueue ( Image<unsigned char>* ) ;				    // Puts back a frame inside the buffer

	void push ( Image<unsigned char>* ) ;			            	    // The provided image is copied into the buffer
} ;

#endif
