/*
  Copyright (c) 2022 FirstBuild
*/

#ifndef ENCODERS_H
#define ENCODERS_H

#include <Arduino.h>

#define ENCODER_MIN_POSITION     0
#define ENCODER_MAX_POSITION     15

typedef struct
{
   uint16_t rawShiftRegisterData;
   struct
   {
      bool humidityA;
      bool humidityB;
      bool humidityC;
      bool humidityD;
      bool airExchangeA;
      bool airExchangeB;
      bool airExchangeC;
      bool airExchangeD;
      bool lightA;
      bool lightB;
      bool lightC;
      bool lightD;
   } inputs;
} Encoders_t;

uint8_t Encoders_GetHumiditySetting(void);

uint8_t Encoders_GetAirExchangeSetting(void);

uint8_t Encoders_GetLightSetting(void);

void Encoders_LogHeader(void);

void Encoders_LogInfo(void);

void Encoders_Run(void);

void Encoders_Init(void);

#endif    // ENCODERS_H
