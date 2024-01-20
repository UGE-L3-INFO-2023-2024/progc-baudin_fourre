/**
 * @file Timer.c
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions allowing to retrieve the current time and manage it
 * @date 2024-01-03
 *
 */

#include "Timer.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Timestamp time_now(void) {
    Timestamp time;
    if (clock_gettime(CLOCK_REALTIME, &time) < 0) {
        perror("Clock time error");
        exit(EXIT_FAILURE);
    }
    return time;
}

Timestamp time_add_seconds(Timestamp time, double seconds) {
    Timestamp interval;
    interval.tv_sec = (time_t) seconds;
    interval.tv_nsec =
        (long) (seconds * 1000000000L) - interval.tv_sec * 1000000000L;

    Timestamp new_time = {
        .tv_sec = time.tv_sec + interval.tv_sec,
        .tv_nsec = time.tv_nsec + interval.tv_nsec,
    };
    if (new_time.tv_nsec >= 1000000000L) {
        new_time.tv_sec++;
        new_time.tv_nsec -= 1000000000L;
    }
    return new_time;
}

// Returns the number of seconds `elapsed` since `time`
double elapsed_since(Timestamp time) {
    Timestamp cur_time = time_now();
    long time_nsec = (time.tv_sec * 1000000000L) + time.tv_nsec;
    long cur_time_nsec = (cur_time.tv_sec * 1000000000L) + cur_time.tv_nsec;
    return (double) (cur_time_nsec - time_nsec) / 1000000000L;
}

// Returns the number of seconds left until `time`
double time_to(Timestamp time) {
    if (is_past_time(time))
        return 0;
    Timestamp cur_time = time_now();
    long time_nsec = (time.tv_sec * 1000000000L) + time.tv_nsec;
    long cur_time_nsec = (cur_time.tv_sec * 1000000000L) + cur_time.tv_nsec;
    return (double) (time_nsec - cur_time_nsec) / 1000000000L;
}

Timestamp time_future(double seconds) {
    Timestamp now = time_now();
    return time_add_seconds(now, seconds);
}

bool is_past_time(Timestamp time) {
    Timestamp now = time_now();
    return (time.tv_sec == now.tv_sec) ? (time.tv_nsec < now.tv_nsec)
                                       : (time.tv_sec < now.tv_sec);
}
