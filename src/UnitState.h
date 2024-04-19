/*
  Copyright (c) 2022 FirstBuild
*/

#ifndef UNIT_STATE_H
#define UNIT_STATE_H

#include <tiny_fsm.h>

void State_StartUp(struct tiny_fsm_t* _fsm, tiny_fsm_signal_t signal, const void* data);

void State_Normal(struct tiny_fsm_t* _fsm, tiny_fsm_signal_t signal, const void* data);

void State_Abnormal(struct tiny_fsm_t* _fsm, tiny_fsm_signal_t signal, const void* data);

void State_HumidityFault(struct tiny_fsm_t* _fsm, tiny_fsm_signal_t signal, const void* data);

void UnitState_LogHeader(void);

void UnitState_LogInfo(void);

void UnitState_Run(void);

void UnitState_Init(void);

#endif   // UNIT_STATE_H
