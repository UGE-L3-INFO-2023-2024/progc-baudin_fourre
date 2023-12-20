#include "Time.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

Timestamp time_now() {
    Timestamp time;
    if (clock_gettime(CLOCK_REALTIME, &time) < 0) {
        perror("Clock time error");
        exit(EXIT_FAILURE);
    }
    return time;
}

Timestamp time_add_seconds(Timestamp time, double seconds) {
    Timestamp interval;
    interval.tv_sec = seconds;
    interval.tv_nsec = (seconds - interval.tv_sec) * 1000000000L;

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

Timestamp time_future(double seconds) {
    Timestamp now = time_now();
    return time_add_seconds(now, seconds);
}

bool is_past_time(Timestamp time) {
    Timestamp now = time_now();
    return (time.tv_sec == now.tv_sec) ? (time.tv_nsec < now.tv_nsec) : (time.tv_sec < now.tv_sec);
}

// gcc src/Time.c -Iinclude/ -o TestTime
/*
int main(int argc, char const *argv[])
{
    printf("Bonjour\n");

    Timestamp sec4 = time_future(4.0);

    while (!is_past_time(sec4)) {
        continue;
    }

    printf("Quatre secondes plus tard\n");

    return 0;
}
*/
