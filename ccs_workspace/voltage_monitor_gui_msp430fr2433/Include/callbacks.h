/*
 * callbacks.h
 */

#include <msp430.h>
#include <stdbool.h>
#include <stdint.h>
#include <GUI.h>
#include <Include/GUIComm.h>

#ifndef INCLUDE_CALLBACKS_H_
#define INCLUDE_CALLBACKS_H_

// Global variables for the callbacks
#ifdef __ENABLE_GUI__
// #defines for communication protocol commands
#define RTC_READ_TIME        0      // Reads current timestamp
#define RTC_WRITE_TIME       1      // Sets new timestamp
#define RTC_READ_THR_HIGH    2      // Reads latest high threshold timestamp
#define RTC_READ_THR_LOW     3      // Reads latest low threshold timestamp
#define ADC_READ_THR_HIGH    4      // Reads current high threshold value
#define ADC_READ_THR_LOW     5      // Reads current low threshold value
#define ADC_WRITE_THR_HIGH   6      // Sets new high threshold value
#define ADC_WRITE_THR_LOW    7      // Sets new low threshold value

// #defines for initial window comparator voltage thresholds
#define ADC_THR_HIGH_MAX     1023   // Maximum high threshold
#define ADC_THR_HIGH_INIT    818    // (818 / 1023) x VREF = ~1.2V, VREF = 1.5V
#define ADC_THR_LOW_INIT     682    // (682 / 1023) x VREF = ~1.0V, VREF = 1.5V
#endif

// Global variables for the callbacks
extern volatile uint8_t command, byteCount;
extern volatile uint16_t voltageThrNew;
extern volatile uint32_t timeStampNew;

// Functions to receive data from GUI
extern void GUICallback_GetRTCData(char * string);
extern void GUICallback_SetRTCData(char * string);
extern void GUICallback_GetRTCHiData(char * string);
extern void GUICallback_GetRTCLoData(char * string);
extern void GUICallback_GetADCHiData(char * string);
extern void GUICallback_GetADCLoData(char * string);
extern void GUICallback_SetADCHiData(char * string);
extern void GUICallback_SetADCLoData(char * string);

#endif /* INCLUDE_CALLBACKS_H_ */
