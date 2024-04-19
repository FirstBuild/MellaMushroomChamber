/*
  Copyright (c) 2022 FirstBuild
*/

#ifndef LIGHT_CONTROLLER_H
#define LIGHT_CONTROLLER_H

#include <Arduino.h>
#include "GrayCodeDecoder.h"

typedef enum {
   LightMode_Normal,
   LightMode_Fault,
   LightMode_Max
} LightMode_t;

typedef struct {
   struct {
      LightMode_t mode;
      uint8_t brightness;
      uint8_t output;
   } _private;
} LightController_t;

void LightController_SetMode(LightMode_t mode);

void LightController_LogHeader(void);

void LightController_LogInfo(void);

void LightController_Run(void);

void LightController_Init(void);

#endif   // LIGHT_CONTROLLER_H
