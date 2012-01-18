#include <vision/image/image.h>
#include <vision/io/imageio.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <ctime>

#ifndef WIN32
#include <sys/time.h>
#endif

#include <vision/win32/windows.h>

#define SEARCH_SIZE 30 
#define WIN_SIZE 5

inline void time_diff(const timeval & tv_in, const timeval & tv_out, timeval & tv_diff)
{
    if( tv_out.tv_sec < tv_in.tv_sec || (tv_out.tv_sec == tv_in.tv_sec && tv_out.tv_usec < tv_in.tv_usec) )
    {
        time_diff(tv_out, tv_in, tv_diff);
    }
    else
    {
        if(tv_out.tv_usec < tv_in.tv_usec)
        {
            tv_diff.tv_sec = tv_out.tv_sec - tv_in.tv_sec - 1;
            tv_diff.tv_usec = 1000000 - tv_in.tv_usec + tv_out.tv_usec;
        }
        else
        {
            tv_diff.tv_sec = tv_out.tv_sec - tv_in.tv_sec;
            tv_diff.tv_usec = tv_out.tv_usec - tv_in.tv_usec;
        }
    }
}

inline void change_pixel(vision::Image<uint32_t, vision::RGB> & img, int y, int x, uint32_t value)
{
    if(x >= 0 && x < img.width && y >= 0 && y < img.height)
    {
        img[y][x] = value;
    }
}

/* The aim of this test is to test the correspondance between two images */

using namespace vision;

void usage(const char * prog_name)
{
    std::cerr << "[Usage] : " << prog_name << " [left image] [right image]" << std::endl;
}

double RGB_2_GRAY ( uint32_t P1 ) {

	uint32_t R = P1 & 0x0000FF ;
	uint32_t G = P1 & 0x00FF00 >> 8 ;
	uint32_t B = P1 & 0xFF0000 >> 16 ;
//	std::cout << R << " " << G << " " << B << std::endl ;
	return ( R + G + B ) / 3.0 ;

}


int main(int argc, char * argv[])
{
    if(argc <= 2)
    {
        usage(argv[0]);
        return 1;
    }

    unsigned int x0 = 360 ;
    unsigned int y0 = 405 ;

    unsigned int Rx = x0 ;
    unsigned int Ry = y0 ;

    std::stringstream ss_left;
    ss_left << argv[1];
    std::string simg_left = ss_left.str();
    
    std::stringstream ss_right;
    ss_right << argv[2];
    std::string simg_right = ss_right.str();
    

    Image<uint32_t, RGB> * img_left = load_color<uint32_t, RGB>(simg_left);
    Image<uint32_t, RGB> * img_right = load_color<uint32_t, RGB>(simg_right);

    (*img_left)[y0][x0] = 0x00FF00 ;

    
    // *** Recherche meilleur Candidat 
    
    double result ;
    result = 1e16 ; 

    timeval tv_in;
    timeval tv_out;
    timeval tv_diff;
    gettimeofday(&tv_in, 0);
   
    int xstart = x0 - SEARCH_SIZE;
    xstart = xstart<0?0:xstart;
    int ystart = y0 - SEARCH_SIZE;
    ystart = ystart<0?0:ystart;
    int xend = x0 + SEARCH_SIZE;
    xend = xend>img_left->width?img_left->width:xend;
    int yend = y0 + SEARCH_SIZE;
    yend = yend>img_left->height?img_left->height:yend;
    for ( int ii = xstart; ii <= xend; ii++ )
    for ( int jj = ystart; jj <= yend; jj++ ) {

	double score = 0 ;

	for ( int wx = -WIN_SIZE; wx <= WIN_SIZE; wx++ )
	for ( int wy = -WIN_SIZE; wy <= WIN_SIZE; wy++ ) {

		uint32_t P_left  = (*img_left)[y0+wy][x0+wx] ;
		uint32_t P_right = (*img_right)[jj+wy][ii+wx] ;

		int32_t R_left = P_left & 0x0000FF ;
		int32_t G_left = P_left & 0x00FF00 >> 8 ;
		int32_t B_left = P_left & 0xFF0000 >> 16 ;

		int32_t R_right = P_right & 0x0000FF ;
		int32_t G_right = P_right & 0x00FF00 >> 8 ;
		int32_t B_right = P_right & 0xFF0000 >> 16 ;

		double R_diff = fabs( (double)R_left - (double)R_right ) ;
		double G_diff = fabs( (double)G_left - (double)G_right ) ;
		double B_diff = fabs( (double)B_left - (double)B_right ) ;
		
		score += R_diff + G_diff + B_diff ;

	}

	if ( score < result ) {
		result = score ;
		Rx = ii ;
		Ry = jj ;

	}


    }

    gettimeofday(&tv_out, 0);
    time_diff(tv_in, tv_out, tv_diff);
    std::cout << "Match took: " << (tv_diff.tv_sec + ((float)tv_diff.tv_usec/1000000)) << "s" << std::endl;
    
    // *** Dessin du cadre de recherche

    for ( int i = - SEARCH_SIZE ; i <= SEARCH_SIZE ; i ++ ) {

    	change_pixel(*img_right,y0 + i,x0 + SEARCH_SIZE, 0x0000FF) ;
    	change_pixel(*img_right,y0 + i,x0 - SEARCH_SIZE, 0x0000FF) ;
    	change_pixel(*img_right,y0 - SEARCH_SIZE,x0 + i, 0x0000FF) ;
    	change_pixel(*img_right,y0 + SEARCH_SIZE,x0 + i, 0x0000FF) ;
    }
    
    // *** Resultat de la recherche
    
	(*img_right)[Ry][Rx] = 0x00FF00 ;

    // 

    save_color<uint32_t, RGB>("/tmp/LEFT.png", img_left);
    save_color<uint32_t, RGB>("/tmp/RIGHT.png", img_right);


    delete img_left;
    delete img_right;

    return 0 ;


}
 
