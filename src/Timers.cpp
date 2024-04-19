/*
  Copyright (c) 2022 FirstBuild
*/

#include "Timers.h"
#include "Parameters.h"
#include "Logging.h"
extern "C"
{
#include "tiny_time_source.h"
#include "tiny_timer.h"
#include "tiny_utils.h"
}

static tiny_timer_group_t timerGroup;
static i_tiny_time_source_t *timeSource = tiny_time_source_init();
static tiny_timer_t timers[TimerId_Max] = { 0, };
static TimersCallback_t callbacks[TimerId_Max] = { 0, };

static void Callback(void *context)
{
   reinterpret(id, context, TimerId_t *);
   callbacks[*id]();
}

void Timers_SetupOneShotTimer(TimerId_t id, TimersCallback_t callback, uint32_t delayMs)
{
   callbacks[id] = callback;

   tiny_timer_start(
      &timerGroup,
      &timers[id],
      delayMs,
      &id,
      Callback);
}

void Timers_SetupPeriodicTimer(TimerId_t id, TimersCallback_t callback, uint32_t delayMs)
{
   callbacks[id] = callback;

   tiny_timer_start_periodic(
      &timerGroup,
      &timers[id],
      delayMs,
      &id,
      Callback);
}

void Timers_Run(void)
{
   tiny_timer_group_run(&timerGroup);
}

void Timers_Init(void)
{
   tiny_timer_group_init(&timerGroup, timeSource);
}
