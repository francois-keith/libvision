#include <visionlib/image.h>
#include <visionlib/imagebuffer.h>

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

int ImageBuffer::get_size() {
	return size ;
}

Image<unsigned char>* ImageBuffer::dequeue() {
	
	if ( size == 0 ) {
		return NULL ;
	}

	ImageBuffer_elem* tmp ;
	Image<unsigned char>*	im ;
	
	tmp = First ;
	First = tmp->Next ;
	First->Prev = tmp->Prev ;
	
	im = tmp->image ;
	
	tmp->Prev = 0 ;
	tmp->image = NULL ;
	tmp->Next = Trash ;
	Trash = tmp ;

	size -= 1 ;

	return im ;

}



