#ifndef __EVENTS_H__
#define __EVENTS_H__

typedef enum {
    NOEVENT,
    QUIT,
} Event;

/**
 * @brief Gets the keyboard event from the user, if there's one
 *
 * @return Event the event retrieved, or else NOEVENT
 */
Event get_events(void);

#endif  // __EVENTS_H__
