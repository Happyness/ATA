#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "eventQue.h"
#include "linkedList.h"

static void my_event_cb(const struct event *evt, void *data)
{
	/* do stuff and things with the event */
}

int runEvent(struct event_cb cb, eventType * type)
{
	
}