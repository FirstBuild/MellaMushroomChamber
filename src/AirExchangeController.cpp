/*
  Copyright (c) 2022 FirstBuild
*/

#include "AirExchangeController.h"
#include "Parameters.h"
#include "PinDefinitions.h"
#include "Encoders.h"
#include "Logging.h"
#include "Timers.h"
#include "Macros.h"

static AirExchangeController_t instance;
static uint32_t lastCycleMillis = 0;
static uint32_t airExchangeCyclingDelayMs = 0;

static void FanCycleDisable(void);

static void FanCycleEnable(void)
{
   instance._private.enabled = true;
   lastCycleMillis = millis();
   airExchangeCyclingDelayMs = PARAMETER_AIR_EXCHANGE_FAN_ON_DURATION_SEC * MS_PER_SEC;
   Timers_SetupOneShotTimer(TimerId_AirExchangeCycling, FanCycleDisable, airExchangeCyclingDelayMs);
   Logging_Verbose_1("Enabling AX Fan for %lu sec", (airExchangeCyclingDelayMs/1000));
}

static void FanCycleDisable(void)
{
   instance._private.enabled = false;
   lastCycleMillis = millis();
   airExchangeCyclingDelayMs = PARAMETER_AIR_EXCHANGE_FAN_OFF_DURATION_SEC * MS_PER_SEC;
   Timers_SetupOneShotTimer(TimerId_AirExchangeCycling, FanCycleEnable, airExchangeCyclingDelayMs);
   Logging_Verbose_1("Disabling AX Fan for %lu", (airExchangeCyclingDelayMs/1000));
}

static bool IsCycleEnabled(void)
{
   return instance._private.enabled;
}

static String GetStatusAsString(void)
{
   return (IsCycleEnabled() == true) ? "Enabled" : "Disabled";
}

static uint16_t GetStatusTimeRemaining(void)
{
   uint16_t cyclingDelay = (airExchangeCyclingDelayMs / MS_PER_SEC);
   uint16_t secSinceLastCycle = ((millis() - lastCycleMillis) / MS_PER_SEC);

   return (cyclingDelay - secSinceLastCycle);
}

static void UpdateSetpointFromKnob(void)
{
   uint8_t knobSetting = Encoders_GetAirExchangeSetting();

   instance._private.setPoint = map(
      knobSetting,
      ENCODER_MIN_POSITION,
      ENCODER_MAX_POSITION,
      PARAMETER_AIR_EXCHANGE_MIN_SETPOINT,
      PARAMETER_AIR_EXCHANGE_MAX_SETPOINT);
}

static void RampFanToOff(void)
{
   if(instance._private.output <= PARAMETER_AIR_EXCHANGE_FAN_MIN_OUTPUT)
   {
      instance._private.output = 0;
   }
   else
   {
      instance._private.output -= PARAMETER_AIR_EXCHANGE_FAN_RAMP_STEP;
   }
}

static void RampFanToSetSpeed(void)
{
   if(VALUE_IN_BOUNDS(instance._private.output, instance._private.setPoint - PARAMETER_AIR_EXCHANGE_FAN_RAMP_STEP, instance._private.setPoint + PARAMETER_AIR_EXCHANGE_FAN_RAMP_STEP))
   {
      instance._private.output = instance._private.setPoint;
   }
   else if(instance._private.output < instance._private.setPoint)
   {
      instance._private.output += PARAMETER_AIR_EXCHANGE_FAN_RAMP_STEP;
   }
   else
   {
      instance._private.output -= PARAMETER_AIR_EXCHANGE_FAN_RAMP_STEP;
   }
}

static uint8_t GetAnalogOutputValue(void)
{
   if(instance._private.output == 0)
   {
      return 0;
   }
   else
   {
      return map(instance._private.output, 1, 100, PARAMETER_AIR_EXCHANGE_FAN_MIN_OUTPUT, PARAMETER_AIR_EXCHANGE_FAN_MAX_OUTPUT);
   }
}

static void RampOutput(void)
{
   if(IsCycleEnabled())
   {
      RampFanToSetSpeed();
   }
   else
   {
      RampFanToOff();
   }

   analogWrite(AIR_EXCHANGE_OUTPUT_PIN, GetAnalogOutputValue());
}

void AirExchangeController_LogHeader(void)
{
   Logging_Info_Data("AX Set, ");
   Logging_Info_Data("AX Status, ");
   Logging_Info_Data("AX Remain, ");
   Logging_Info_Data("AX Output, ");
   Logging_Info_Data("|, ");
}

void AirExchangeController_LogInfo(void)
{
   Logging_Info_Data_1("%4u %%, ", instance._private.setPoint);
   Logging_Info_Data_1("%9s, ", GetStatusAsString().c_str());
   Logging_Info_Data_1("%5u sec, ", GetStatusTimeRemaining());
   Logging_Info_Data_1("%7u %%, ", instance._private.output);
   Logging_Info_Data("|, ");
}

void AirExchangeController_Run(void)
{
   UpdateSetpointFromKnob();
   RampOutput();
}

static void SetupPwmOutput(void)
{
   // Configure Timer 1
   TCCR1A = 0b00000001; // Phase Correct PWM Mode, 8-bit, TOP = 0xFF
   TCCR1B = 0b00000100; // Divide I/O clock by 256 (8MHz / 256 = 31,250 Hz)

   pinMode(AIR_EXCHANGE_OUTPUT_PIN, OUTPUT);
}

void AirExchangeController_Init(void)
{
   SetupPwmOutput();
   FanCycleEnable();
}
