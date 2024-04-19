/*
  Copyright (c) 2022 FirstBuild
*/

#ifndef HUMIDITY_CONTROLLER_H
#define HUMIDITY_CONTROLLER_H

#include <Adafruit_SHT31.h>

typedef struct {
   struct {
      double setPoint;
      double sensorValue;
      Adafruit_SHT31 sensor;
      int16_t pidRequest;
      int16_t outputValue;
      uint16_t integratorNegativeWindupCounter;
      uint16_t integratorPositiveWindupCounter;
   } _private;
} HumidityController_t;

bool HumidityController_ValueIsNormal(void);

void HumidityController_LogHeader(void);

void HumidityController_LogInfo(void);

void HumidityController_Run(void);

void HumidityController_Init(void);

#endif   // HUMIDITY_CONTROLLER_H
