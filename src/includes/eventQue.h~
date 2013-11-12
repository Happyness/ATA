/*
 Author: 	Joel Denke
 Description: 	Que to handling events with event callbacks
 Created:	25 april 2012
 */

#ifndef _EVENTQUE_H
#define _EVENTQUE_H

typedef enum {eEorld, eCoordinates, eInput} eventType;

struct event {
	int no, callback;
	eventType type;
};

typedef void (*event_cb_t)(const struct event *evt, void *userdata);

int event_cb_register(event_cb_t cb, void *userdata);

struct event_cb {
	event_cb_t cb;
	void *data;
};

/*
 Author: 	Joel Denke
 Description: 	Run event callback
 Params:	struct event_cb, An event callback
		enum eventType, Type of event
 Return value: Depends
 */
int runEvent(struct event_cb, eventType *);
#endif