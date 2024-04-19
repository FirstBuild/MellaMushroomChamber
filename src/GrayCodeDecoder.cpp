/*
  Copyright (c) 2022 FirstBuild
*/

#include "GrayCodeDecoder.h"
#include "Logging.h"

GrayCodePosition_t GrayCodeRawTranslation[16] =
{
   GrayCodePosition_10,
   GrayCodePosition_11,
   GrayCodePosition_13,
   GrayCodePosition_12,
   GrayCodePosition_5,
   GrayCodePosition_4,
   GrayCodePosition_2,
   GrayCodePosition_3,
   GrayCodePosition_9,
   GrayCodePosition_8,
   GrayCodePosition_14,
   GrayCodePosition_15,
   GrayCodePosition_6,
   GrayCodePosition_7,
   GrayCodePosition_1,
   GrayCodePosition_0,
};

uint8_t GrayCodeDecoder_GetPosition(GrayCodeDecoder_t *instance)
{
   uint8_t valA, valB, valC, valD;
   valA = *instance->pinA;
   valB = *instance->pinB;
   valC = *instance->pinC;
   valD = *instance->pinD;

   uint8_t rawGrayCode = 0;
   rawGrayCode += (valA << 3);
   rawGrayCode += (valB << 2);
   rawGrayCode += (valC << 1);
   rawGrayCode += (valD);
   Logging_Debug_1("\nRaw Graycode: %i", rawGrayCode);

   uint8_t retVal = 0;
   retVal = GrayCodeRawTranslation[rawGrayCode];
   Logging_Debug_1("Graycode Position: %i", retVal);
   return (GrayCodePosition_t)retVal;
}

void GrayCodeDecoder_Init(GrayCodeDecoder_t *instance, bool *pinA, bool *pinB, bool *pinC, bool *pinD)
{
   instance->pinA = pinA;
   instance->pinB = pinB;
   instance->pinC = pinC;
   instance->pinD = pinD;
}
