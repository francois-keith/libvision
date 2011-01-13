template <typename T>
GenericCamera<T>::GenericCamera( uint64_t id ) {
	gid = id ;
	active = false ;
	size.x = 1 ;
	size.y = 1 ;
}

template <typename T>
GenericCamera<T>::~GenericCamera() {
}

template <typename T>
uint64_t GenericCamera<T>::get_gid() {
	return gid ;
}

template <typename T>
ImageRef GenericCamera<T>::get_size() {
	return size ;
}

template <typename T>
void GenericCamera<T>::set_size ( int x, int y ) {
	size.x = x ;
	size.y = y ;
}


