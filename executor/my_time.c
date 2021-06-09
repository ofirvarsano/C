#include "my_time.h"
#include <unistd.h> /* useconds_t */
#include <stdio.h>
#define MILLION 1000000
#define BILLION 1000000000

TaskTime Time_Convert(double _interval)
{
	TaskTime time;
	_interval += 0.5e-9;
	time.tv_sec = (long)_interval;
	time.tv_nsec = (_interval - (long)_interval) * BILLION;
	return time;
}

TaskTime time_add(TaskTime _time1, TaskTime _time2)
{
	TaskTime result;
	if ((_time1.tv_nsec + _time2.tv_nsec) >= BILLION)
	{
		result.tv_sec = _time1.tv_sec + _time2.tv_sec + 1;
		result.tv_nsec = _time1.tv_nsec + _time2.tv_nsec - BILLION;
	}
	else
	{
		result.tv_sec = _time1.tv_sec + _time2.tv_sec;
		result.tv_nsec = _time1.tv_nsec + _time2.tv_nsec;
	}
	return result;
}

TaskTime Time_CalcNextTime(TaskTime _interval)
{
	TaskTime time;
	clock_gettime(CLOCK_REALTIME, &time);
	return time_add(_interval, time);
}

static long specToMicro(TaskTime _time)
{
	return (long)(_time.tv_sec * MILLION + _time.tv_nsec / 1000);
}

TaskTime Time_SleepUntill(TaskTime _next)
{
	TaskTime time;
	long nextMicro, currMicro, difference;
	clock_gettime(CLOCK_REALTIME, &time);
	
	nextMicro = specToMicro(_next);
	currMicro = specToMicro(time);
	
	difference = nextMicro - currMicro;
	if (difference > 0)
	{
		usleep((useconds_t)difference);
	}
	return time;
}

int Time_IsLess(TaskTime _time1, TaskTime _time2)
{
	return specToMicro(_time1) < specToMicro(_time2);
}

