/*
 * callbacks_JSON.c
 */

#include <callbacks.h>

#ifdef __ENABLE_GUI__
void GUICallback_GetRTCData(char * string)
{
    byteCount = 1;
    command = RTC_READ_TIME;
}

void GUICallback_SetRTCData(char * string)
{
    byteCount = 5;
    command = RTC_WRITE_TIME;
    timeStampNew = strtol(string, NULL, 10);
}

void GUICallback_GetRTCHiData(char * string)
{
    byteCount = 1;
    command = RTC_READ_THR_HIGH;
}

void GUICallback_GetRTCLoData(char * string)
{
    byteCount = 1;
    command = RTC_READ_THR_LOW;
}

void GUICallback_GetADCHiData(char * string)
{
    byteCount = 1;
    command = ADC_READ_THR_HIGH;
}

void GUICallback_GetADCLoData(char * string)
{
    byteCount = 1;
    command = ADC_READ_THR_LOW;
}

void GUICallback_SetADCHiData(char * string)
{
    byteCount = 3;
    command = ADC_WRITE_THR_HIGH;
    voltageThrNew = strtol(string, NULL, 10);
}

void GUICallback_SetADCLoData(char * string)
{
    byteCount = 3;
    command = ADC_WRITE_THR_LOW;
    voltageThrNew = strtol(string, NULL, 10);
}
#endif
