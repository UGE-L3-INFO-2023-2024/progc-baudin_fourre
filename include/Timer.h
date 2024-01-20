/**
 * @file Timer.h
 * @author Anaelle Fourré & Florian Baudin
 * @brief Provides functions allowing to retrieve the current time and manage it
 * @date 2024-01-03
 *
 */

#ifndef __TIME_H__
#define __TIME_H__

#define _DEFAULT_SOURCE 1
#include <stdbool.h>
#include <time.h>

/**
 * @brief Structure representing a timestamp
 */
typedef struct timespec Timestamp;

/**
 * @brief Gets the current time
 *
 * @return the current time
 */
Timestamp time_now(void);

/**
 * @brief Adds `seconds` to `time`
 *
 * @param time the time to add to
 * @param seconds the number of seconds to add
 * @return the new time with `seconds` added
 */
Timestamp time_add_seconds(Timestamp time, double seconds);

/**
 * @brief Gets the current time plus `seconds`
 *
 * @param seconds the number of seconds to add to the current time
 * @return the current time with `seconds` added
 */
Timestamp time_future(double seconds);

/**
 * @brief Checks if `time` is in the past
 *
 * @param time the time to check
 * @return true if `time` is in the past, false otherwise
 */
bool is_past_time(Timestamp time);

/**
 * @brief Gets the time elapsed since `time`
 *
 * @param time the time to compare to
 * @return time elapsed, in seconds
 */
double elapsed_since(Timestamp time);

/**
 * @brief Gets the time left until `time`
 *
 * @param time the time to compare to
 * @return time left, in seconds
 */
double time_to(Timestamp time);

#endif // __TIME_H__
