/*
 * callbacks_JSON.c
 */

#include <callbacks.h>

void GUICallback_Second(char * string)
{
    sIncrement = strtol(string, NULL, 10);

#if defined(__ENABLE_GUI__)
    TI_second=sIncrement/10*16+sIncrement%10;
#endif
}

void GUICallback_Minute(char * string)
{
    sIncrement = strtol(string, NULL, 10);

#if defined(__ENABLE_GUI__)
    TI_minute=sIncrement/10*16+sIncrement%10;
#endif
}

void GUICallback_Hour(char * string)
{
    sIncrement = strtol(string, NULL, 10);

#if defined(__ENABLE_GUI__)
    TI_hour=sIncrement/10*16+sIncrement%10;
#endif
}

void GUICallback_Day(char * string)
{
    sIncrement = strtol(string, NULL, 10);

#if defined(__ENABLE_GUI__)
    TI_day=sIncrement/10*16+sIncrement%10;
#endif
}

void GUICallback_Month(char * string)
{
    sIncrement = strtol(string, NULL, 10)-1;

#if defined(__ENABLE_GUI__)
    TI_month=sIncrement/10*16+sIncrement%10;
#endif
}

void GUICallback_Year(char * string)
{
    sIncrement = strtol(string, NULL, 10);

#if defined(__ENABLE_GUI__)
    TI_year=(sIncrement)/1000*4096+(sIncrement)/100%10*256+(sIncrement)/10%10*16+(sIncrement) % 10;
#endif
}

void GUICallback_PM(char * string)
{
    sIncrement = strtol(string, NULL, 10);

#if defined(__ENABLE_GUI__)
    TI_PM=sIncrement;
#endif
}

void GUICallback_Timeset_Done(char * string)
{
    commandFlag=0;
    P1OUT &= ~BIT1;
}
