/*
  Copyright (c) 2022 FirstBuild
*/

#include "Encoders.h"
#include "PinDefinitions.h"
#include "GrayCodeDecoder.h"
#include "Macros.h"
#include "Logging.h"

static Encoders_t instance;
static GrayCodeDecoder_t humidityDecoder;
static GrayCodeDecoder_t airExchangeDecoder;
static GrayCodeDecoder_t lightDecoder;

static void ReadShiftRegister(void)
{
   digitalWrite(SHIFT_REGISTER_CLOCK_ENABLE, HIGH);
   digitalWrite(SHIFT_REGISTER_LOAD, LOW);
   delayMicroseconds(5);
   digitalWrite(SHIFT_REGISTER_LOAD, HIGH);
   digitalWrite(SHIFT_REGISTER_CLOCK_ENABLE, LOW);
   instance.rawShiftRegisterData = 0;

   for(int i = 0; i < 16; i++)
   {
      instance.rawShiftRegisterData |= (digitalRead(SHIFT_REGISTER_DATA) << (15 - i));
      digitalWrite(SHIFT_REGISTER_CLOCK_IN, HIGH);
      delayMicroseconds(5);
      digitalWrite(SHIFT_REGISTER_CLOCK_IN, LOW);
   }
}

static void ProcessInputs(void)
{
   ReadShiftRegister();

   instance.inputs.humidityA = CHECK_BIT(instance.rawShiftRegisterData, 0);
   instance.inputs.humidityB = CHECK_BIT(instance.rawShiftRegisterData, 1);
   instance.inputs.humidityC = CHECK_BIT(instance.rawShiftRegisterData, 2);
   instance.inputs.humidityD = CHECK_BIT(instance.rawShiftRegisterData, 3);
   instance.inputs.airExchangeA = CHECK_BIT(instance.rawShiftRegisterData, 7);
   instance.inputs.airExchangeB = CHECK_BIT(instance.rawShiftRegisterData, 6);
   instance.inputs.airExchangeC = CHECK_BIT(instance.rawShiftRegisterData, 5);
   instance.inputs.airExchangeD = CHECK_BIT(instance.rawShiftRegisterData, 4);
#ifdef LIGHT_ENCODER_DIRECT
   instance.inputs.lightA = digitalRead(LIGHT_KNOB_PIN_A);
   instance.inputs.lightB = digitalRead(LIGHT_KNOB_PIN_B);
   instance.inputs.lightC = digitalRead(LIGHT_KNOB_PIN_C);
   instance.inputs.lightD = digitalRead(LIGHT_KNOB_PIN_D);
#else
   instance.inputs.lightA = CHECK_BIT(instance.rawShiftRegisterData, 8);
   instance.inputs.lightB = CHECK_BIT(instance.rawShiftRegisterData, 9);
   instance.inputs.lightC = CHECK_BIT(instance.rawShiftRegisterData, 10);
   instance.inputs.lightD = CHECK_BIT(instance.rawShiftRegisterData, 11);
#endif

}

uint8_t Encoders_GetHumiditySetting(void)
{
   uint8_t retVal = GrayCodeDecoder_GetPosition(&humidityDecoder);
   return retVal;
}

uint8_t Encoders_GetAirExchangeSetting(void)
{
   uint8_t retVal = GrayCodeDecoder_GetPosition(&airExchangeDecoder);
   return retVal;
}

uint8_t Encoders_GetLightSetting(void)
{
   uint8_t retVal = GrayCodeDecoder_GetPosition(&lightDecoder);
   return retVal;
}

void Encoders_LogHeader(void)
{
   Logging_Debug("");
   Logging_Debug_1("Humidity Encoder A: %u", instance.inputs.humidityA);
   Logging_Debug_1("Humidity Encoder B: %u", instance.inputs.humidityB);
   Logging_Debug_1("Humidity Encoder C: %u", instance.inputs.humidityC);
   Logging_Debug_1("Humidity Encoder D: %u", instance.inputs.humidityD);
   Logging_Debug("");
   Logging_Debug_1("Air Exchange Encoder A: %u", instance.inputs.airExchangeA);
   Logging_Debug_1("Air Exchange Encoder B: %u", instance.inputs.airExchangeB);
   Logging_Debug_1("Air Exchange Encoder C: %u", instance.inputs.airExchangeC);
   Logging_Debug_1("Air Exchange Encoder D: %u", instance.inputs.airExchangeD);
   Logging_Debug("");
   Logging_Debug_1("Light Encoder A: %u", instance.inputs.lightA);
   Logging_Debug_1("Light Encoder B: %u", instance.inputs.lightB);
   Logging_Debug_1("Light Encoder C: %u", instance.inputs.lightC);
   Logging_Debug_1("Light Encoder D: %u", instance.inputs.lightD);
   Logging_Debug("");
   Logging_Debug_1("Shift Register Raw Data: 0x%02X", instance.rawShiftRegisterData);
   Logging_Debug("");

   Logging_Info_Data("LL Knob, ");
   Logging_Info_Data("RH Knob, ");
   Logging_Info_Data("AX Knob, ");
   Logging_Info_Data("|, ");
}

void Encoders_LogInfo(void)
{
   Logging_Info_Data_2("%4i/%i, ", Encoders_GetLightSetting(), ENCODER_MAX_POSITION);
   Logging_Info_Data_2("%4i/%i, ", Encoders_GetHumiditySetting(), ENCODER_MAX_POSITION);
   Logging_Info_Data_2("%4i/%i, ", Encoders_GetAirExchangeSetting(), ENCODER_MAX_POSITION);
   Logging_Info_Data("|, ");
}

void Encoders_Run(void)
{
   ProcessInputs();
}

void Encoders_Init(void)
{
   pinMode(SHIFT_REGISTER_LOAD, OUTPUT);
   pinMode(SHIFT_REGISTER_CLOCK_IN, OUTPUT);
   pinMode(SHIFT_REGISTER_CLOCK_ENABLE, OUTPUT);
   pinMode(SHIFT_REGISTER_DATA, INPUT);
   pinMode(LIGHT_KNOB_PIN_A, INPUT_PULLUP);
   pinMode(LIGHT_KNOB_PIN_B, INPUT_PULLUP);
   pinMode(LIGHT_KNOB_PIN_C, INPUT_PULLUP);
   pinMode(LIGHT_KNOB_PIN_D, INPUT_PULLUP);

   digitalWrite(SHIFT_REGISTER_CLOCK_IN, LOW);
   digitalWrite(SHIFT_REGISTER_LOAD, HIGH);

   GrayCodeDecoder_Init(&humidityDecoder, &instance.inputs.humidityA, &instance.inputs.humidityB, &instance.inputs.humidityC, &instance.inputs.humidityD);
   GrayCodeDecoder_Init(&airExchangeDecoder, &instance.inputs.airExchangeA, &instance.inputs.airExchangeB, &instance.inputs.airExchangeC, &instance.inputs.airExchangeD);
   GrayCodeDecoder_Init(&lightDecoder, &instance.inputs.lightA, &instance.inputs.lightB, &instance.inputs.lightC, &instance.inputs.lightD);
}
