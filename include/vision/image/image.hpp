template<typename Pix, int ColorSpace>
Image<Pix, ColorSpace>::Image( ImageRef ir ) 
{
  width = ir.x;
  height = ir.y;
  pixels = ir.x*ir.y ;
  size = ImageRef(ir.x,ir.y) ;
  pixel_size = sizeof ( Pix ) ;
  data_size = pixels * pixel_size ;
  raw_data = new Pix[pixels];
  if (raw_data == NULL)
    throw "new[] error" ;
}

template<typename Pix, int ColorSpace>
Image<Pix, ColorSpace>::Image( const Image<Pix,ColorSpace> &img ) 
{
  width = img.width ;
  height = img.height ;
  pixels = img.pixels ;
  size = img.size ;
  pixel_size = img.pixel_size ;
  data_size = img.data_size ;
  raw_data = new Pix[pixels];
  if (raw_data == NULL)
    throw "new[] error" ;
  std::memcpy ( img.raw_data, raw_data, data_size ) ;
}

template<typename Pix, int ColorSpace> 
Image<Pix, ColorSpace>::Image (unsigned int w, unsigned int h)
{
  width = w;
  height = h;
  pixels = w * h;
  size = ImageRef(w,h) ;
  pixel_size = sizeof ( Pix ) ;
  data_size = pixels * pixel_size ;
  raw_data = new Pix[pixels];
  if (raw_data == NULL)
    throw "new[] error" ;
}

template<typename Pix, int ColorSpace>
Image<Pix, ColorSpace>::~Image ()
{
	delete[] raw_data;
}

template <typename Pix, int ColorSpace>
Pix* Image<Pix, ColorSpace>::operator[] ( unsigned int line ) {
	return &(raw_data[line*width] ) ;
}

template <typename Pix, int ColorSpace>
Pix& Image<Pix, ColorSpace>::operator()(ImageRef coord)
{
	return raw_data[coord.x+coord.y*width] ;
}

template <typename Pix, int ColorSpace>
Pix& Image<Pix, ColorSpace>::operator()(unsigned int x, unsigned int y)
{
	return raw_data[x+y*width] ;
}

template<typename Pix, int ColorSpace>
Image<Pix,ColorSpace>* Image<Pix,ColorSpace>::clone() {
	Image<Pix,ColorSpace>* img ;
	img = new Image<Pix,ColorSpace>(width,height) ;
	std::memcpy ( img->raw_data, raw_data, data_size ) ;
	return img ;
}

template<typename Pix, int ColorSpace>
void Image<Pix,ColorSpace>::copy( Image<Pix,ColorSpace> *src ) {
	
	if ( data_size == src->data_size )
		std::memcpy ( raw_data, src->raw_data, data_size ) ;
	return ;
}
