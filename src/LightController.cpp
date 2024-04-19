/*
  Copyright (c) 2022 FirstBuild
*/

#include "LightController.h"
#include "PinDefinitions.h"
#include "Parameters.h"
#include "Encoders.h"
#include "Logging.h"

static LightController_t instance;
static uint32_t animationStep = 0;
static bool lastHeartbeartState = LOW;
static uint16_t lastHeartbeartSec = 0;

void LightController_SetMode(LightMode_t mode)
{
   if(mode < LightMode_Max)
   {
      instance._private.mode = mode;
      animationStep = 0;
   }
}

static void GetBrightnessFromKnob(void)
{
   instance._private.brightness = map(
      Encoders_GetLightSetting(),
      ENCODER_MIN_POSITION,
      ENCODER_MAX_POSITION,
      0,
      100);
}


static bool GetNormalHeartbeatLedState(void)
{
   uint16_t sec = (millis() / MS_PER_SEC);

   if(sec >= (lastHeartbeartSec + (PARAMETER_LIGHTS_HEARTBEAT_NORMAL_DELAY_MS / MS_PER_SEC)))
   {
      lastHeartbeartSec = sec;
      lastHeartbeartState = !lastHeartbeartState;
   }
   return (lastHeartbeartState);
}

static bool GetFaultHeartbeatLedState(void)
{
   uint16_t sec = (millis() / MS_PER_SEC);

   if(sec >= lastHeartbeartSec + (PARAMETER_LIGHTS_HEARTBEAT_FAULT_DELAY_MS / MS_PER_SEC))
   {
      lastHeartbeartSec = sec;
      lastHeartbeartState = !lastHeartbeartState;
   }
   return (lastHeartbeartState);
}

static void RunNormalMode(void)
{
   instance._private.output = ((0 == instance._private.brightness) ? 0 : map(instance._private.brightness, 1, 100, PARAMETER_LIGHTS_MIN_SETPOINT, PARAMETER_LIGHTS_MAX_SETPOINT));
   analogWrite(LIGHT_OUTPUT_PIN, instance._private.output);
   digitalWrite(ON_BOARD_LED_PIN, GetNormalHeartbeatLedState());
}

static uint8_t GetSawtoothBrightness(void)
{
   int32_t retVal = map((millis() % PARAMETER_LIGHTS_FAULT_BREATHE_PERIOD_MS), 0, PARAMETER_LIGHTS_FAULT_BREATHE_PERIOD_MS, PARAMETER_MIN_ANALOG_OUTPUT, PARAMETER_MAX_ANALOG_OUTPUT * 2);
   retVal = (retVal <= PARAMETER_MAX_ANALOG_OUTPUT) ? retVal : (PARAMETER_MAX_ANALOG_OUTPUT - retVal);
   return int(retVal);
}

static void RunFaultMode(void)
{
   instance._private.output = GetSawtoothBrightness();
   analogWrite(LIGHT_OUTPUT_PIN, instance._private.output);
   digitalWrite(ON_BOARD_LED_PIN, GetFaultHeartbeatLedState());
}

static bool IsInFaultMode(void)
{
   return instance._private.mode == LightMode_Fault;
}

void LightController_LogHeader(void)
{
   Logging_Info_Data("LL Setting, ");
   Logging_Info_Data("LL Mode, ");
   Logging_Info_Data("LL Output, ");
   Logging_Info_Data("|, ");
}

void LightController_LogInfo(void)
{
   Logging_Info_Data_1("%7u %%, ", (uint16_t)map(instance._private.output, 0, PARAMETER_MAX_ANALOG_OUTPUT, 0, 100));

   if(IsInFaultMode())
   {
      Logging_Info_Data("  Fault, ");
   }
   else
   {
      Logging_Info_Data("  Normal, ");
   }

   Logging_Info_Data_1("%7li %%, ", map(instance._private.output, 0, PARAMETER_MAX_ANALOG_OUTPUT, 0, 100));
   Logging_Info_Data("|, ");
}

void LightController_Run(void)
{
   GetBrightnessFromKnob();
   if(instance._private.mode == LightMode_Fault)
   {
      RunFaultMode();
   }
   else
   {
      RunNormalMode();
   }
}

void LightController_Init(void)
{
   pinMode(LIGHT_OUTPUT_PIN, OUTPUT);
   pinMode(ON_BOARD_LED_PIN, OUTPUT);
   LightController_SetMode(LightMode_Normal);
}
