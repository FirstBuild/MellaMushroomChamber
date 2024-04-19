/*
  Copyright (c) 2022 FirstBuild
*/

#include "UnitState.h"
#include "Parameters.h"
#include "HumidityController.h"
#include "LightController.h"
#include "Logging.h"

#define SIGNAL_ENTRY tiny_fsm_signal_entry
#define SIGNAL_EXIT  tiny_fsm_signal_exit
#define SIGNAL_TICK  tiny_fsm_signal_user_start


static uint16_t delayTimeSeconds = 0;

static tiny_fsm_t fsm;

void State_Startup(tiny_fsm_t* _fsm, tiny_fsm_signal_t signal, const void* data);
void State_Normal(tiny_fsm_t* _fsm, tiny_fsm_signal_t signal, const void* data);
void State_Abnormal(tiny_fsm_t* _fsm, tiny_fsm_signal_t signal, const void* data);
void State_HumidityFault(tiny_fsm_t* _fsm, tiny_fsm_signal_t signal, const void* data);

static const char* StateName(void)
{
   static String name;
   if(State_StartUp == fsm.current)
      name = "Startup";
   else if(State_Normal == fsm.current)
      name = "Normal";
   else if(State_Abnormal == fsm.current)
      name = "Abnormal";
   else if(State_HumidityFault == fsm.current)
      name = "RH Fault";

   return name.c_str();
}

static void Tock(void)
{
   static unsigned long lastSec = 0;
   unsigned long thisSec = millis() / 1000;

   if(thisSec != lastSec)
   {
      lastSec = thisSec;

      // If a delay has been specified, decrement it.
      if (delayTimeSeconds > 0)
      {
         delayTimeSeconds--;
      }
   }
}

static bool DelayTimeIsComplete(void)
{
   return (delayTimeSeconds == 0);
}

static void Fsm_Signal(tiny_fsm_signal_t _signal)
{
   fsm.current(&fsm, _signal, NULL);
}

static void Fsm_Transition(tiny_fsm_state_t _state)
{
   Fsm_Signal(SIGNAL_EXIT);
   fsm.current = _state;
   Fsm_Signal(SIGNAL_ENTRY);
}

void State_StartUp(tiny_fsm_t* _fsm, tiny_fsm_signal_t signal, const void* data)
{
   switch((uint8_t)signal)
   {
      case SIGNAL_ENTRY:
         LightController_SetMode(LightMode_Normal);
         delayTimeSeconds = PARAMETER_STARTUP_FAULT_DELAY_SEC;
         break;
      case SIGNAL_TICK:
         if(DelayTimeIsComplete())
         {
            Fsm_Transition(State_Normal);
         }
         break;
      case SIGNAL_EXIT:
         break;
      default:
         break;
   }
}

void State_Normal(tiny_fsm_t* _fsm, tiny_fsm_signal_t signal, const void* data)
{
   switch((uint8_t)signal)
   {
      case SIGNAL_ENTRY:
         LightController_SetMode(LightMode_Normal);
         break;
      case SIGNAL_TICK:
         if(!HumidityController_ValueIsNormal())
         {
            Fsm_Transition(State_Abnormal);
         }
         break;
      case SIGNAL_EXIT:
         break;
      default:
         break;
   }
}

void State_Abnormal(tiny_fsm_t* _fsm, tiny_fsm_signal_t signal, const void* data)
{
   switch((uint8_t)signal)
   {
      case SIGNAL_ENTRY:
         LightController_SetMode(LightMode_Normal);
         delayTimeSeconds = PARAMETER_STEADYSTATE_FAULT_DELAY_SEC;
         break;
      case SIGNAL_TICK:
         if(HumidityController_ValueIsNormal())
         {
            Fsm_Transition(State_Normal);
         }
         else if(DelayTimeIsComplete())
         {
            Fsm_Transition(State_HumidityFault);
         }
         break;
      case SIGNAL_EXIT:
         // Required since we can exit based on the value becoming normal (not just time).
         delayTimeSeconds = 0;
         break;
      default:
         break;
   }
}

void State_HumidityFault(tiny_fsm_t* _fsm, tiny_fsm_signal_t signal, const void* data)
{
   switch((uint8_t)signal)
   {
      case SIGNAL_ENTRY:
         LightController_SetMode(LightMode_Fault);
         break;
      case SIGNAL_TICK:
         if(HumidityController_ValueIsNormal())
         {
            Fsm_Transition(State_Normal);
         }
         break;
      case SIGNAL_EXIT:
         break;
      default:
         break;
   }
}

void UnitState_LogHeader(void)
{
   Logging_Info_Data("    Delay Sec, ");
   Logging_Info_Data("    State, ");
   Logging_Info_Data("|, ");
}

void UnitState_LogInfo(void)
{
   Logging_Info_Data_1("%4u, ", delayTimeSeconds);
   Logging_Info_Data_1("%9s, ", StateName());
   Logging_Info_Data("|, ");
}

void UnitState_Run(void)
{
   Fsm_Signal(SIGNAL_TICK);
   Tock();
}

void UnitState_Init(void)
{
   tiny_fsm_init(&fsm, State_StartUp);
}
