#include <vision/image/image.h>
#include <vision/io/imageio.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <ctime>

#define SEARCH_SIZE 30 
#define WIN_SIZE 5


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

    unsigned int x0 = 100 ;
    unsigned int y0 = 200 ;

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
   
    for ( int ii = x0 - SEARCH_SIZE; ii <= x0 + SEARCH_SIZE; ii++ )
    for ( int jj = y0 - SEARCH_SIZE; jj <= y0 + SEARCH_SIZE; jj++ ) {

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

		double R_diff = fabs( R_left - R_right ) ;
		double G_diff = fabs( G_left - G_right ) ;
		double B_diff = fabs( B_left - B_right ) ;
		
		score += R_diff + G_diff + B_diff ;

	}

	if ( score < result ) {
		result = score ;
		Rx = ii ;
		Ry = jj ;

	}


    }
    
    // *** Dessin du cadre de recherche

    for ( int i = - SEARCH_SIZE ; i <= SEARCH_SIZE ; i ++ ) {

    	(*img_right)[y0 + i][x0 + SEARCH_SIZE ] = 0x0000FF ;
    	(*img_right)[y0 + i][x0 - SEARCH_SIZE ] = 0x0000FF ;
    	(*img_right)[y0 - SEARCH_SIZE][x0 + i ] = 0x0000FF ;
    	(*img_right)[y0 + SEARCH_SIZE][x0 + i ] = 0x0000FF ;
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
 
