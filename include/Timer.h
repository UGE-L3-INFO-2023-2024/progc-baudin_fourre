#ifndef __TIME_H__
#define __TIME_H__

#define _DEFAULT_SOURCE 1
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>

typedef struct timespec Timestamp;

Timestamp time_now();

Timestamp time_add_seconds(Timestamp time, double seconds);

Timestamp time_future(double seconds);

bool is_past_time(Timestamp time);

/**
 * @brief Gets the time elapsed since `time`
 *
 * @param time
 * @return double time elapsed, in seconds
 */
double elapsed_since(Timestamp time);

/**
 * @brief Gets the time left until `time`
 *
 * @param time
 * @return double time left, in seconds
 */
double time_to(Timestamp time);

#endif // __TIME_H__