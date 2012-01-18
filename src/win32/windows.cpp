#include <vision/win32/windows.h>

#include <stdint.h>

void gettimeofday(timeval * tv, void *)
{
	if(tv)
	{
		FILETIME ft;
		GetSystemTimeAsFileTime(&ft);
		uint64_t t_now;
		t_now |= ft.dwHighDateTime;
		t_now <<= 32;
		t_now |= ft.dwLowDateTime;
		t_now /= 10; /* back to microsec */
		tv->tv_sec  = t_now / 1000000ul;
		tv->tv_usec = t_now % 1000000ul;
	}
}

void sleep(unsigned int sec)
{
	Sleep(sec*1000);
}

void usleep(unsigned int usec)
{
	Sleep(usec/1000);
}