/*
 * callbacks.h
 */

#include <msp430.h>
#include <stdbool.h>
#include <stdint.h>
#include <GUI.h>
#include <Include/GUIComm.h>
#include "RTC_Calendar.h"

#ifndef INCLUDE_CALLBACKS_H_
#define INCLUDE_CALLBACKS_H_

// Global variables for the callbacks
extern volatile uint8_t commandFlag;
volatile unsigned int sIncrement;

// Functions to receive data from GUI
extern void GUICallback_QMathData(char * string);
extern void GUICallback_Second(char * string);
extern void GUICallback_Minute(char * string);
extern void GUICallback_Hour(char * string);
extern void GUICallback_Day(char * string);
extern void GUICallback_Month(char * string);
extern void GUICallback_Year(char * string);
extern void GUICallback_PM(char * string);
extern void GUICallback_Timeset_Done(char * string);

//extern void GUICallback_boolEnable(char * string);

#endif /* INCLUDE_CALLBACKS_H_ */
