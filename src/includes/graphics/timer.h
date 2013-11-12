#ifndef _H_TIMER
#define _H_TIMER

#include <SDL.h>

#define FPS 60

/**
 * Author: Robin & Sarah
 * Description: This file is used for calculation Frames per seconds. with diffrent option like using
 *              timer start, stop, pause, unpause, and one very important get_tickets.
 */

struct timer_t2
{
  int startTicks;
  int pausedTicks;
  int paused;
  int started;
};

void timer_init (struct timer_t2 * timer);
void timer_start(struct timer_t2 * timer);
void timer_stop(struct timer_t2 * timer);
void timer_pause(struct timer_t2 * timer);
void timer_unpause(struct timer_t2 *timer);
int timer_get_ticks(struct timer_t2 *timer);
int timer_is_started(struct timer_t2 *timer);
int timer_is_paused(struct timer_t2 *timer);

#endif



