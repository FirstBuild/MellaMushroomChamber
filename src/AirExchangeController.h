/*
  Copyright (c) 2022 FirstBuild
*/

#ifndef AIR_EXCHANGE_CONTROLLER_H
#define AIR_EXCHANGE_CONTROLLER_H

#include "Parameters.h"
#include "GrayCodeDecoder.h"

typedef struct {
   struct {
      uint8_t setPoint;
      uint8_t output;
      bool enabled;
   } _private;
} AirExchangeController_t;

void AirExchangeController_LogHeader(void);

void AirExchangeController_LogInfo(void);

void AirExchangeController_Run(void);

void AirExchangeController_Init(void);

#endif   // AIR_EXCHANGE_CONTROLLER_H
