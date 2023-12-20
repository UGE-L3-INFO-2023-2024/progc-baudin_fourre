#ifndef __TIME_H__
#define __TIME_H__

#define _DEFAULT_SOURCE 1
#include <time.h>
#include <stdbool.h>

typedef struct timespec Timestamp;

Timestamp time_now();

Timestamp time_add_seconds(Timestamp time, double seconds);

Timestamp time_future(double seconds);

bool is_past_time(Timestamp time);

#endif  // __TIME_H__
