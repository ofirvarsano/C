#ifndef __MY_TIME_H__
#define __MY_TIME_H__
#include <time.h> /* timespec */

typedef struct timespec TaskTime;

TaskTime Time_Convert(double _interval);

TaskTime Time_CalcNextTime(TaskTime _interval);

TaskTime Time_SleepUntill(TaskTime _next);

int Time_IsLess(TaskTime _time1, TaskTime _time2);

TaskTime time_add(TaskTime _time1, TaskTime _time2);

#endif /*__MY_TIME_H__*/
