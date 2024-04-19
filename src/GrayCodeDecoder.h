/*
  Copyright (c) 2022 FirstBuild
*/

#ifndef GRAY_CODE_DECODER_H
#define GRAY_CODE_DECODER_H

#include <Arduino.h>

typedef enum
{
   GrayCodePosition_0,
   GrayCodePosition_1,
   GrayCodePosition_2,
   GrayCodePosition_3,
   GrayCodePosition_4,
   GrayCodePosition_5,
   GrayCodePosition_6,
   GrayCodePosition_7,
   GrayCodePosition_8,
   GrayCodePosition_9,
   GrayCodePosition_10,
   GrayCodePosition_11,
   GrayCodePosition_12,
   GrayCodePosition_13,
   GrayCodePosition_14,
   GrayCodePosition_15,
} GrayCodePosition_t;

typedef struct
{
   bool *pinA;
   bool *pinB;
   bool *pinC;
   bool *pinD;
} GrayCodeDecoder_t;

uint8_t GrayCodeDecoder_GetPosition(GrayCodeDecoder_t *instance);

void GrayCodeDecoder_Init(GrayCodeDecoder_t *instance, bool *pinA, bool *pinB, bool *pinC, bool *pinD);

#endif   // GRAY_CODE_DECODER_H
