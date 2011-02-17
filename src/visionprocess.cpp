#include <vision/imagebuffer.h>
#include <vision/visionprocess.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <iostream>

using namespace std ;

VisionProcess::VisionProcess( VisionServer* srv, string name ) {
	
	vision_server = srv ;
	process_name = name ;
	path_config = srv->get_plugin_path() + process_name + "/" ;
	config_file = path_config + "plugin.conf" ;

	mkdir( path_config.c_str() , S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	err.open( (path_config + "err.log" ).c_str() , ios::out ) ;
	out.open( (path_config + "out.log" ).c_str() , ios::out ) ;
	
}


VisionProcess::~VisionProcess() {
	for ( int i=0; i< buffers.size(); i++ )
		delete ( buffers[i] ) ;
}


int VisionProcess::push_image ( Image<unsigned char> *img, int numcam ) {
	buffers[numcam]->push( img ) ;
}


Image<unsigned char>* VisionProcess::dequeue_image( int i ) {
	return buffers[i]->dequeue() ;
}


void VisionProcess::enqueue_image( Image<unsigned char>* img, int i ) {
	buffers[i]->enqueue ( img ) ;
}


string VisionProcess::get_name() { 
	return process_name ; 
}

string VisionProcess::get_configpath() {
	return path_config ;
}

string VisionProcess::get_configfile() {
	
	ifstream fichier ;						// test if the file exists. If not, create it
	fichier.open ( config_file.c_str() ) ;
	if ( fichier.fail() ) {
		ofstream nvfile ;
		nvfile.open ( config_file.c_str() , ios::out ) ;
		nvfile.close() ;
	}

	return config_file ;
}

void VisionProcess::register_to_cam ( int i ) {

	int nbuff ;
	ImageRef size ;

	size = vision_server->get_camera(i)->get_size() ;

	ImageBuffer * tmp = new ImageBuffer(size, 5);
	buffers.push_back ( tmp ) ;

	nbuff = buffers.size() - 1 ;

	vision_server->register_to_cam ( this, i, nbuff ) ; 

	out << "Registered to cam " << i << endl ;

}

