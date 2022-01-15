/*
 * timerp.cpp
 *
 *  Created on: Jan 14, 2022
 *      Author: vityha
 */

#include "timerp.h"

void initTimer(void) {
    Timer_A_initUpModeParam initUpModeParam = {0};
    initUpModeParam.clockSource = TIMER_A_CLOCKSOURCE_ACLK;
    initUpModeParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_64;
    initUpModeParam.timerPeriod = 2500;
    initUpModeParam.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    initUpModeParam.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE;
    initUpModeParam.timerClear = TIMER_A_DO_CLEAR;
    initUpModeParam.startTimer = true;
    Timer_A_initUpMode(TIMER_A0_BASE, &initUpModeParam);
}


