#include <iostream>

#include <string.h>

#include <visionlib/image.h>
#include <visionlib/imagebuffer.h>

using namespace std ;

ImageBuffer::ImageBuffer ( ImageRef img_size, int N ) {

	First = NULL ;
	size  = 0 ;
	Trash = NULL ;

	for (int i=0; i<N; i++ ) {
		ImageBuffer_elem *tmp ;
		tmp = new ImageBuffer_elem ;
		tmp->Prev = NULL ;
		tmp->Next = Trash ;
		Trash = tmp ;
	}

	for (int i=0; i<N; i++) {
		Image<unsigned char>* img ;
		img = new Image<unsigned char> ( img_size.x, img_size.y ) ;
		enqueue ( img ) ;
	}

	size = N ;
		
}

ImageBuffer::~ImageBuffer () {


	while ( size != 0 ) {
		Image<unsigned char>* img = dequeue() ;
		delete img ;
	}

	while ( Trash != NULL ) {
		ImageBuffer_elem *tmp ;
		tmp = Trash ;
		Trash = Trash->Next ;
		delete tmp ;
	}

}

Image<unsigned char>* ImageBuffer::dequeue() {
	
	
	while (size==0 ) {
		usleep (10 ) ;
	}
	
	ImageBuffer_elem* tmp ;
	Image<unsigned char>*	im ;
	
	tmp = First ;

	if (size != 1 ) {
		First = tmp->Next ;
		First->Prev = tmp->Prev ;
		First->Prev->Next = First ;
	} else { 
		First = NULL ;
	}
	
	im = tmp->image ;
	
	tmp->Prev = NULL ;
	tmp->image = NULL ;
	tmp->Next = Trash ;
	Trash = tmp ;

	size -= 1 ;

	return im ;

}

void ImageBuffer::enqueue( Image<unsigned char>* img ) {
	
	if ( Trash == NULL ) {
		cerr << " ERREUR " << endl ;
		exit(0) ;
	}

	ImageBuffer_elem* tmp ;
	tmp = Trash ;

	Trash = tmp->Next ;

	if (First != NULL ) {
		tmp->Next = First ;
		tmp->Prev = First->Prev ;

		First->Prev->Next = tmp ;
		First->Prev = tmp ;
	} else {
		tmp->Next = tmp ;
		tmp->Prev = tmp ;
		First = tmp ;
	}

	tmp->image = img ;

	size += 1 ;
}

void ImageBuffer::push  ( Image<unsigned char>* img ) {

	if ( size == 0 ) {
		cerr << " Cannot push in empty stack " << endl ;
		exit(0) ;
	}

	memcpy( First->Prev->image->get_raw_data(), 
			img->get_raw_data(), 
			img->get_width() * img->get_height() * sizeof (unsigned char ) ) ;

	First = First->Prev ;

}






