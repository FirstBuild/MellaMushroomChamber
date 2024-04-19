/*
  Copyright (c) 2022 FirstBuild
*/

/**
 * @file Logging.h
 * @author Bobby Lindsey
 * @date 21 April 2022
 * @brief Logging funtions with multiple levels
 */

#ifndef LOGGING_H
#define LOGGING_H

#include "Arduino.h"
#include "Parameters.h"

/**
 * @breif Log a message with one variable at LogLevel_Debug
 */
#define Logging_Debug_1(_m, _a) \
if(LogLevel_Debug <= PARAMETER_LOG_LEVEL) \
{ \
   char message[255]; \
   sprintf(message, _m, _a); \
   Logging_Debug(message); \
}

/**
 * @breif Log a message with two variables at LogLevel_Debug
 */
#define Logging_Debug_2(_m, _a, _b) \
if(LogLevel_Debug <= PARAMETER_LOG_LEVEL) \
{ \
   char message[255]; \
   sprintf(message, _m, _a, _b); \
   Logging_Debug(message); \
}

/**
 * @breif Log a message with three variables at LogLevel_Debug
 */
#define Logging_Debug_3(_m, _a, _b, _c) \
if(LogLevel_Debug <= PARAMETER_LOG_LEVEL) \
{ \
   char message[255]; \
   sprintf(message, _m, _a, _b, _c); \
   Logging_Debug(message); \
}

/**
 * @breif Log a message with one variable at LogLevel_Debug
 */
#define Logging_Verbose_1(_m, _a) \
if(LogLevel_Verbose <= PARAMETER_LOG_LEVEL) \
{ \
   char message[255]; \
   sprintf(message, _m, _a); \
   Logging_Verbose(message); \
}

/**
 * @breif Log a message with two variables at LogLevel_Verbose
 */
#define Logging_Verbose_2(_m, _a, _b) \
if(LogLevel_Verbose <= PARAMETER_LOG_LEVEL) \
{ \
   char message[255]; \
   sprintf(message, _m, _a, _b); \
   Logging_Verbose(message); \
}

/**
 * @breif Log a message with three variables at LogLevel_Verbose
 */
#define Logging_Verbose_3(_m, _a, _b, _c) \
if(LogLevel_Verbose <= PARAMETER_LOG_LEVEL) \
{ \
   char message[255]; \
   sprintf(message, _m, _a, _b, _c); \
   Logging_Verbose(message); \
}

/**
 * @breif Log a message with one variable at LogLevel_Debug
 */
#define Logging_Verbose_Data_1(_m, _a) \
if(LogLevel_Verbose <= PARAMETER_LOG_LEVEL) \
{ \
   char message[255]; \
   sprintf(message, _m, _a); \
   Logging_Verbose_Data(message); \
}

/**
 * @breif Log a message with two variables at LogLevel_Verbose
 */
#define Logging_Verbose_Data_2(_m, _a, _b) \
if(LogLevel_Verbose <= PARAMETER_LOG_LEVEL) \
{ \
   char message[255]; \
   sprintf(message, _m, _a, _b); \
   Logging_Verbose_Data(message); \
}

/**
 * @breif Log a message with three variables at LogLevel_Verbose
 */
#define Logging_Verbose_Data_3(_m, _a, _b, _c) \
if(LogLevel_Verbose <= PARAMETER_LOG_LEVEL) \
{ \
   char message[255]; \
   sprintf(message, _m, _a, _b, _c); \
   Logging_Verbose_Data(message); \
}

/**
 * @breif Log a message with one variable at LogLevel_Info
 */
#define Logging_Info_1(_m, _a) \
if(LogLevel_Info <= PARAMETER_LOG_LEVEL) \
{ \
   char message[255]; \
   sprintf(message, _m, _a); \
   Logging_Info(message); \
}

/**
 * @breif Log a message with two variables at LogLevel_Info
 */
#define Logging_Info_2(_m, _a, _b) \
if(LogLevel_Info <= PARAMETER_LOG_LEVEL) \
{ \
   char message[255]; \
   sprintf(message, _m, _a, _b); \
   Logging_Info(message); \
}

/**
 * @breif Log a message with three variables at LogLevel_Info
 */
#define Logging_Info_3(_m, _a, _b, _c) \
if(LogLevel_Info <= PARAMETER_LOG_LEVEL) \
{ \
   char message[255]; \
   sprintf(message, _m, _a, _b, _c); \
   Logging_Info(message); \
}

/**
 * @breif Log a message with three variables at LogLevel_Info
 */
#define Logging_Info_4(_m, _a, _b, _c, _d) \
if(LogLevel_Info <= PARAMETER_LOG_LEVEL) \
{ \
   char message[255]; \
   sprintf(message, _m, _a, _b, _c, _d); \
   Logging_Info(message); \
}

/**
 * @breif Log a message with one variable at LogLevel_Info
 */
#define Logging_Info_Data_1(_m, _a) \
if(LogLevel_Info <= PARAMETER_LOG_LEVEL) \
{ \
   char message[255]; \
   sprintf(message, _m, _a); \
   Logging_Info_Data(message); \
}

/**
 * @breif Log a message with one variable at LogLevel_Info
 */
#define Logging_Info_Data_2(_m, _a, _b) \
if(LogLevel_Info <= PARAMETER_LOG_LEVEL) \
{ \
   char message[255]; \
   sprintf(message, _m, _a, _b); \
   Logging_Info_Data(message); \
}

/**
 * @breif Log a message with one variable at LogLevel_Info
 */
#define Logging_Info_Data_3(_m, _a, _b, _c) \
if(LogLevel_Info <= PARAMETER_LOG_LEVEL) \
{ \
   char message[255]; \
   sprintf(message, _m, _a, _b, _c); \
   Logging_Info_Data(message); \
}

/**
 * @breif Log a message with one variable at LogLevel_Info
 */
#define Logging_Info_Data_4(_m, _a, _b, _c, _d) \
if(LogLevel_Info <= PARAMETER_LOG_LEVEL) \
{ \
   char message[255]; \
   sprintf(message, _m, _a, _b, _c, _d); \
   Logging_Info_Data(message); \
}

typedef enum {
   LogLevel_None,
   LogLevel_Info,
   LogLevel_Verbose,
   LogLevel_Debug,
} LogLevel_t;

/**
 * @brief Log a message without carrige return at LogLevel_Debug
 *
 * @param message The string to be logged
 */
void Logging_Debug_Data(char const *message);

/**
 * @brief Log a message without carrige return at LogLevel_Verbose
 *
 * @param message The string to be logged
 */
void Logging_Verbose_Data(char const *message);

/**
 * @brief Log a message without carrige return at LogLevel_Info
 *
 * @param message The string to be logged
 */
void Logging_Info_Data(char const *message);

/**
 * @brief Log a message at LogLevel_Debug
 *
 * @param message The string to be logged
 */
void Logging_Debug(char const *message);

/**
 * @brief Log a message at LogLevel_Verbose
 *
 * @param message The string to be logged
 */
void Logging_Verbose(char const *message);

/**
 * @brief Log a message at LogLevel_Info
 *
 * @param message The string to be logged
 */
void Logging_Info(char const *message);

/**
 * @brief Setup logging for later use
 */
void Logging_Init(void);

#endif // LOGGING_H
