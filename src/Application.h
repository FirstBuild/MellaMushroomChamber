/*
  Copyright (c) 2022 FirstBuild
*/

#ifndef APPLICATION_H
#define APPLICATION_H

#include "AirExchangeController.h"
#include "HumidityController.h"
#include "LightController.h"

typedef struct {
   AirExchangeController_t airExchangeController;
   HumidityController_t humidityController;
   LightController_t lightController;
} Application_t;

void Application_Every1Sec(void);

void Application_Log(void);

void Application_Tick(void);

void Application_Run(void);

void Application_Init(void);

#endif   // APPLICATION_H
