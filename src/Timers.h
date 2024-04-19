/*
  Copyright (c) 2022 FirstBuild
*/

#ifndef TIMERS_H
#define TIMERS_H

#include "Arduino.h"

typedef enum {
   TimerId_Application,
   TimerId_Logging,
   TimerId_AirExchangeCycling,
   TimerId_Max,
} TimerId_t;

typedef void (*TimersCallback_t)(void);

void Timers_SetupOneShotTimer(TimerId_t id, TimersCallback_t callback, uint32_t ms);

void Timers_SetupPeriodicTimer(TimerId_t id, TimersCallback_t callback, uint32_t ms);

void Timers_Run(void);

void Timers_Init(void);

#endif // TIMERS_H
