/*
  Copyright (c) 2022 FirstBuild
*/

#include "Logging.h"
#include "Parameters.h"
#include <Arduino.h>

void Logging_Debug_Data(char const *message)
{
   if(LogLevel_Debug <= PARAMETER_LOG_LEVEL)
   {
      Serial.print(message);
   }
}

void Logging_Verbose_Data(char const *message)
{
   if(LogLevel_Verbose <= PARAMETER_LOG_LEVEL)
   {
      Serial.print(message);
   }
}

void Logging_Info_Data(const String literal)
{
   Logging_Info_Data(literal.c_str());
}

void Logging_Info_Data(char const *message)
{
   if(LogLevel_Info <= PARAMETER_LOG_LEVEL)
   {
      Serial.print(message);
   }
}

void Logging_Debug(char const *message)
{
   if(LogLevel_Debug <= PARAMETER_LOG_LEVEL)
   {
      Serial.println(message);
   }
}

void Logging_Verbose(char const *message)
{
   if(LogLevel_Verbose <= PARAMETER_LOG_LEVEL)
   {
      Serial.println(message);
   }
}

void Logging_Info(char const *message)
{
   if(LogLevel_Info <= PARAMETER_LOG_LEVEL)
   {
      Serial.println(message);
   }
}

void Logging_Init(void)
{
   Serial.begin(115200);
}
