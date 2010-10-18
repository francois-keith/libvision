#ifndef ROBOTVISION_IMAGEBUFFER_H
#define ROBOTVISION_IMAGEBUFFER_H

#include "image.h"

template <typename T>
class ImageBuffer {

	private:

	class ImageBuffer_elem {
		Image<T> *image ;
		ImageBuffer_elem *Next ;
		ImageBuffer_elem *Prev ;
	}

	ImageBuffer_elem *First ;
	int size ;

	ImageBuffer_elem *Trash ;


	public:

	ImageBuffer( ImageRef image_size, int N ) ;	    	    // Allocates a ringbuffer of N images (specified size)
	~ImageBuffer() ;

	int  get_size() ;					    // returns the number of images in the ringbuffer
	bool is_empty() ;					    // returns true if the ringbuffer is empty

	Image<T>* dequeue () ;					    // Removes the latest frame from the ringbuffer and returns it
	void enqueue ( Image<T>* ) ;				    // Puts back a frame inside the buffer

	void push ( Image<T>* ) ;			            // The provided image is copied inside the ringbuffer
}

ImageBuffer::ImageBuffer ( ImageRef img_size, int N ) {

	First = NULL ;
	size  = 0 ;
	Bin = NULL ;

	for (int i=0; i<N; i++ ) {
		ImageBuffer_elem *tmp ;
		tmp = new ImageBuffer_elem ;
		tmp->prev = NULL ;
		tmp->Next = Bin ;
		Bin = tmp ;
	}

	for (int i=0; i<N; i++) {
		Image* img ;
		img = new Image ( img_size ) ;
		enqueue ( img ) ;
	}

	size = N ;
		
}

ImageBuffer::~ImageBuffer () {
	while ( size != 0 ) {
		Image* img = dequeue() ;
		delete img ;
	}

	while ( Bin != NULL ) {
		RingBuffer_elem *tmp ;
		tmp = Bin ;
		Bin = Bin->Next ;
		delete tmp ;
	}
}

int ImageBuffer::get_size() {
	return size ;
}

Image* ImageBuffer::dequeue() {
	
	if ( size == 0 ) {
		return NULL ;
	}

	ImageBuffer_elem* tmp ;
	Image*	im ;
	
	tmp = First ;
	First = tmp->Next ;
	First->Previous = tmp>Previous ;
	
	im = tmp->image ;
	
	tmp->Previous = 0 ;
	tmp->image = NULL ;
	tmp->Next = Bin ;
	Bin = tmp ;

	size -= 1 ;

	return im ;

}


void ImageBuffer::enqueue ( Image* img ) {
	if ( 


#endif
