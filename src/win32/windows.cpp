#include <vision/win32/windows.h>

#include <stdint.h>
#include <iostream>

# if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#  define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
# else
#  define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
# endif

void gettimeofday(struct timeval *tv, void *)
{
  FILETIME ft;
  unsigned __int64 tmpres = 0;
  static int tzflag;

  if (NULL != tv)
    {
      GetSystemTimeAsFileTime(&ft);

      tmpres |= ft.dwHighDateTime;
      tmpres <<= 32;
      tmpres |= ft.dwLowDateTime;

      /*converting file time to unix epoch*/
      tmpres /= 10;  /*convert into microseconds*/
      tmpres -= DELTA_EPOCH_IN_MICROSECS;
      tv->tv_sec = (long)(tmpres / 1000000UL);
      tv->tv_usec = (long)(tmpres % 1000000UL);
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