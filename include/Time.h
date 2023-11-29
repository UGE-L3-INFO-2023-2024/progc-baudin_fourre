#ifndef __TIME_H__
#define __TIME_H__

#include <sys/time.h>

typedef struct timeval timestamp;
typedef struct timeval interval;

timestamp add_interval(timestamp time, int seconds);

interval get_interval(float seconds);

// Chronometre

#endif  // __TIME_H__
