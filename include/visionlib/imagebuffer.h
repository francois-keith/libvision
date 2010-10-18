#ifndef ROBOTVISION_IMAGEBUFFER_H
#define ROBOTVISION_IMAGEBUFFER_H

#include "image.h"

class ImageBuffer {

	private:

	class ImageBuffer_elem {
		public:
		Image<unsigned char> *image ;
		ImageBuffer_elem *Next ;
		ImageBuffer_elem *Prev ;
	} ;

	ImageBuffer_elem *First ;
	int size ;

	ImageBuffer_elem *Trash ;


	public:

	ImageBuffer( ImageRef image_size, int N ) ;	    	    // Allocates a ringbuffer of N images (specified size)
	~ImageBuffer() ;

	int  get_size() ;					    // returns the number of images in the ringbuffer
	bool is_empty() ;					    // returns true if the ringbuffer is empty

	Image<unsigned char>* dequeue () ;					    // Removes the latest frame from the ringbuffer and returns it
	void enqueue ( Image<unsigned char>* ) ;				    // Puts back a frame inside the buffer

	void push ( Image<unsigned char>* ) ;			            // The provided image is copied inside the ringbuffer
} ;

#endif
