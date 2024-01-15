/**
 * @file Queue.h
 * @author Anaelle Fourré & Florian Baudin
 * @brief
 * @date 2024-01-05
 *
 */

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <sys/queue.h>

#define LIST_FOREACH_SAFE(var, head, field, tvar)                              \
    for ((var) = LIST_FIRST((head));                                           \
         (var) && ((tvar) = LIST_NEXT((var), field), 1); (var) = (tvar))

#endif // __QUEUE_H__
