#ifndef __LINUXTHREAD_H__
#define __LINUXTHREAD_H__
#ifndef WIN32

#include "pthread.h"

#define Lock pthread_mutex_lock
#define UnLock pthread_mutex_unlock
#define Wait pthread_cond_wait
#define Signal pthread_cond_signal
#define Broadcast pthread_cond_broadcast


class Event
{
private:
	pthread_mutex_t	m;
	pthread_cond_t	c;
	bool cond;

public:
	Event()
	{
		cond = false;
		pthread_mutex_init(&m, NULL);
		pthread_cond_init(&c, NULL);
	}

	~Event()
	{
		pthread_cond_destroy(&c);
		pthread_mutex_destroy(&m);
	}
	
	void SetEvent()
	{
		pthread_mutex_lock(&m);
		cond = true;
		pthread_mutex_unlock(&m);
		pthread_cond_signal(&c);
	}

	void ResetEvent()
	{
		pthread_mutex_lock(&m);
		cond = false;
		pthread_mutex_unlock(&m);
	}

	int WaitEvent(const struct timespec *abstime = NULL)
	{
		int rt = 0;
		pthread_mutex_lock(&m);		
		while(!cond)
		{
			if(abstime == NULL)
			{
				rt = pthread_cond_wait(&c, &m);
			}
			else
			{
				rt = pthread_cond_timedwait(&c, &m, abstime);
			}
		}
		pthread_mutex_unlock(&m);
		return rt;
	}
};

#endif
#endif //__LINUXTHREAD_H__