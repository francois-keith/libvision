#include <iostream>
#include <string.h>

#include <visionlib/image.h>
#include <visionlib/imagebuffer.h>

using namespace std ;

ImageBuffer::ImageBuffer ( ImageRef img_size, int N ) {
	frames.reserve( N ) ;								//FIXME voir comment utiliser mieux le constructeur de vector
	trash.reserve( N ) ;
	pthread_mutex_init(&mutex, NULL);
	for (int i=0; i<N; i++) {
		trash.push_back ( new Image<unsigned char> (img_size.x, img_size.y) ) ;
	}
}

ImageBuffer::~ImageBuffer () {
	for (int i=0; i<frames.size(); i++ )
		delete frames[i] ;
	frames.clear() ;
	for (int i=0; i<trash.size(); i++ )
		delete trash[i] ;
	trash.clear() ;
}

Image<unsigned char>* ImageBuffer::dequeue() {
	Image<unsigned char> * tmp ;
	pthread_mutex_lock( &mutex );
	while ( frames.size() == 0 ) {
		pthread_mutex_unlock( &mutex ) ;
		usleep ( 1000 ) ;
		pthread_mutex_lock ( &mutex ) ;
	}
	tmp = frames.front() ;
	frames.erase(frames.begin()) ;
	pthread_mutex_unlock( &mutex );
	return tmp ;
}

void ImageBuffer::enqueue( Image<unsigned char>* img ) {
	pthread_mutex_lock( &mutex ) ;
	trash.push_back( img ) ;
	pthread_mutex_unlock(&mutex) ;
}

void ImageBuffer::push  ( Image<unsigned char>* img ) {
	Image<unsigned char> *tmp ;
	pthread_mutex_lock( &mutex ) ;
	
	if ( trash.size() == 0 ) {
		pthread_mutex_unlock( &mutex ) ;
		return ;
	}
	
	tmp = trash.back() ;
	trash.pop_back() ;
	memcpy ( tmp->get_raw_data() , img->get_raw_data(), img->get_width() * img->get_height() * sizeof ( unsigned char ) ) ;
	frames.push_back ( tmp ) ;
	pthread_mutex_unlock( &mutex ) ;

}







