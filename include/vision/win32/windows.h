/* This implements a few unix functions used in vision library and visionsystem
that are not available in windows API */

#ifdef WIN32

#include <windows.h>

/* Normally gettimeofday uses timezone as a second argument but this is not
implemented in this version */
void gettimeofday(timeval * tv, void *);

void sleep(unsigned int sec);

void usleep(unsigned int usec);

#endif

