#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <iomanip>
#include <sys/time.h>

/*****************************************************************************/
/*********************** CLASS TIMING ****************************************/
/*****************************************************************************/

/*!This class holds a timer. This timer can be set (restartTime) and text can
   be printed with the elapsed time since the timer was restarted.. */
class Timing
{
#ifdef WIN32
	DWORD  time1;                  /*! < the number of milliseconds that have
	                                       elapsed since the Windows was started */
#else
	struct timeval time1;          /*!< Time the timer has last been restarted.*/
#endif

public:
		// methods to restart the timer, get the elapsed time and print messages
#ifdef WIN32
	static double getTimeDifference    ( DWORD tv1, DWORD tv2                  );
#else
	static double getTimeDifference    ( struct   timeval t1,
					     struct   timeval t2                   );
#endif
	void          printTimeDiffWithText( std::ostream& os,
	                                     char     *str,
	                                     int      iFactor = 1000               );
	double        getElapsedTime       ( int      iFactor = 1                  );
	void          restartTime          (                                       );
};

#endif
