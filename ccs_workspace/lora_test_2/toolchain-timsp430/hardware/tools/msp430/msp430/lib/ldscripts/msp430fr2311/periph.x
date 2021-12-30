/* ============================================================================ */
/* Copyright (c) 2016, Texas Instruments Incorporated                           */
/*  All rights reserved.                                                        */
/*                                                                              */
/*  Redistribution and use in source and binary forms, with or without          */
/*  modification, are permitted provided that the following conditions          */
/*  are met:                                                                    */
/*                                                                              */
/*  *  Redistributions of source code must retain the above copyright           */
/*     notice, this list of conditions and the following disclaimer.            */
/*                                                                              */
/*  *  Redistributions in binary form must reproduce the above copyright        */
/*     notice, this list of conditions and the following disclaimer in the      */
/*     documentation and/or other materials provided with the distribution.     */
/*                                                                              */
/*  *  Neither the name of Texas Instruments Incorporated nor the names of      */
/*     its contributors may be used to endorse or promote products derived      */
/*     from this software without specific prior written permission.            */
/*                                                                              */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" */
/*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,       */
/*  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      */
/*  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR            */
/*  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,       */
/*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,         */
/*  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; */
/*  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,    */
/*  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR     */
/*  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,              */
/*  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                          */
/* ============================================================================ */

/* This file supports MSP430FR2311 devices. */

/* Version: 1.184    (Beta-Build-Tag: #0001) */

/************************************************************
* PERIPHERAL FILE MAP
************************************************************/


/*****************************************************************************
 ADC
*****************************************************************************/
__ADCCTL0            = 0x0700;
__ADCCTL0_L          = 0x0700;
__ADCCTL0_H          = 0x0701;
__ADCCTL1            = 0x0702;
__ADCCTL1_L          = 0x0702;
__ADCCTL1_H          = 0x0703;
__ADCCTL2            = 0x0704;
__ADCCTL2_L          = 0x0704;
__ADCCTL2_H          = 0x0705;
__ADCLO              = 0x0706;
__ADCLO_L            = 0x0706;
__ADCLO_H            = 0x0707;
__ADCHI              = 0x0708;
__ADCHI_L            = 0x0708;
__ADCHI_H            = 0x0709;
__ADCMCTL0           = 0x070A;
__ADCMCTL0_L         = 0x070A;
__ADCMCTL0_H         = 0x070B;
__ADCMEM0            = 0x0712;
__ADCMEM0_L          = 0x0712;
__ADCMEM0_H          = 0x0713;
__ADCIE              = 0x071A;
__ADCIE_L            = 0x071A;
__ADCIE_H            = 0x071B;
__ADCIFG             = 0x071C;
__ADCIFG_L           = 0x071C;
__ADCIFG_H           = 0x071D;
__ADCIV              = 0x071E;
__ADCIV_L            = 0x071E;
__ADCIV_H            = 0x071F;


/*****************************************************************************
 BKMEM
*****************************************************************************/
__BAKMEM0            = 0x0660;
__BAKMEM0_L          = 0x0660;
__BAKMEM0_H          = 0x0661;
__BAKMEM1            = 0x0662;
__BAKMEM1_L          = 0x0662;
__BAKMEM1_H          = 0x0663;
__BAKMEM2            = 0x0664;
__BAKMEM2_L          = 0x0664;
__BAKMEM2_H          = 0x0665;
__BAKMEM3            = 0x0666;
__BAKMEM3_L          = 0x0666;
__BAKMEM3_H          = 0x0667;
__BAKMEM4            = 0x0668;
__BAKMEM4_L          = 0x0668;
__BAKMEM4_H          = 0x0669;
__BAKMEM5            = 0x066A;
__BAKMEM5_L          = 0x066A;
__BAKMEM5_H          = 0x066B;
__BAKMEM6            = 0x066C;
__BAKMEM6_L          = 0x066C;
__BAKMEM6_H          = 0x066D;
__BAKMEM7            = 0x066E;
__BAKMEM7_L          = 0x066E;
__BAKMEM7_H          = 0x066F;
__BAKMEM8            = 0x0670;
__BAKMEM8_L          = 0x0670;
__BAKMEM8_H          = 0x0671;
__BAKMEM9            = 0x0672;
__BAKMEM9_L          = 0x0672;
__BAKMEM9_H          = 0x0673;
__BAKMEM10           = 0x0674;
__BAKMEM10_L         = 0x0674;
__BAKMEM10_H         = 0x0675;
__BAKMEM11           = 0x0676;
__BAKMEM11_L         = 0x0676;
__BAKMEM11_H         = 0x0677;
__BAKMEM12           = 0x0678;
__BAKMEM12_L         = 0x0678;
__BAKMEM12_H         = 0x0679;
__BAKMEM13           = 0x067A;
__BAKMEM13_L         = 0x067A;
__BAKMEM13_H         = 0x067B;
__BAKMEM14           = 0x067C;
__BAKMEM14_L         = 0x067C;
__BAKMEM14_H         = 0x067D;
__BAKMEM15           = 0x067E;
__BAKMEM15_L         = 0x067E;
__BAKMEM15_H         = 0x067F;


/*****************************************************************************
 CAPTIO
*****************************************************************************/
__CAPTIOCTL          = 0x02EE;
__CAPTIOCTL_L        = 0x02EE;
__CAPTIOCTL_H        = 0x02EF;


/*****************************************************************************
 CRC
*****************************************************************************/
__CRCDI              = 0x01C0;
__CRCDI_L            = 0x01C0;
__CRCDI_H            = 0x01C1;
__CRCDIRB            = 0x01C2;
__CRCDIRB_L          = 0x01C2;
__CRCDIRB_H          = 0x01C3;
__CRCINIRES          = 0x01C4;
__CRCINIRES_L        = 0x01C4;
__CRCINIRES_H        = 0x01C5;
__CRCRESR            = 0x01C6;
__CRCRESR_L          = 0x01C6;
__CRCRESR_H          = 0x01C7;


/*****************************************************************************
 CS
*****************************************************************************/
__CSCTL0             = 0x0180;
__CSCTL0_L           = 0x0180;
__CSCTL0_H           = 0x0181;
__CSCTL1             = 0x0182;
__CSCTL1_L           = 0x0182;
__CSCTL1_H           = 0x0183;
__CSCTL2             = 0x0184;
__CSCTL2_L           = 0x0184;
__CSCTL2_H           = 0x0185;
__CSCTL3             = 0x0186;
__CSCTL3_L           = 0x0186;
__CSCTL3_H           = 0x0187;
__CSCTL4             = 0x0188;
__CSCTL4_L           = 0x0188;
__CSCTL4_H           = 0x0189;
__CSCTL5             = 0x018A;
__CSCTL5_L           = 0x018A;
__CSCTL5_H           = 0x018B;
__CSCTL6             = 0x018C;
__CSCTL6_L           = 0x018C;
__CSCTL6_H           = 0x018D;
__CSCTL7             = 0x018E;
__CSCTL7_L           = 0x018E;
__CSCTL7_H           = 0x018F;
__CSCTL8             = 0x0190;
__CSCTL8_L           = 0x0190;
__CSCTL8_H           = 0x0191;


/*****************************************************************************
 DIO
*****************************************************************************/
__PAIN               = 0x0200;
__PAIN_L             = 0x0200;
__PAIN_H             = 0x0201;
__PAOUT              = 0x0202;
__PAOUT_L            = 0x0202;
__PAOUT_H            = 0x0203;
__PADIR              = 0x0204;
__PADIR_L            = 0x0204;
__PADIR_H            = 0x0205;
__PAREN              = 0x0206;
__PAREN_L            = 0x0206;
__PAREN_H            = 0x0207;
__PASEL0             = 0x020A;
__PASEL0_L           = 0x020A;
__PASEL0_H           = 0x020B;
__PASEL1             = 0x020C;
__PASEL1_L           = 0x020C;
__PASEL1_H           = 0x020D;
__P1IV               = 0x020E;
__P1IV_L             = 0x020E;
__P1IV_H             = 0x020F;
__PASELC             = 0x0216;
__PASELC_L           = 0x0216;
__PASELC_H           = 0x0217;
__PAIES              = 0x0218;
__PAIES_L            = 0x0218;
__PAIES_H            = 0x0219;
__PAIE               = 0x021A;
__PAIE_L             = 0x021A;
__PAIE_H             = 0x021B;
__PAIFG              = 0x021C;
__PAIFG_L            = 0x021C;
__PAIFG_H            = 0x021D;
__P2IV               = 0x021E;
__P2IV_L             = 0x021E;
__P2IV_H             = 0x021F;
__PJIN               = 0x0320;
__PJIN_L             = 0x0320;
__PJIN_H             = 0x0321;
__PJOUT              = 0x0322;
__PJOUT_L            = 0x0322;
__PJOUT_H            = 0x0323;
__PJDIR              = 0x0324;
__PJDIR_L            = 0x0324;
__PJDIR_H            = 0x0325;
__PJREN              = 0x0326;
__PJREN_L            = 0x0326;
__PJREN_H            = 0x0327;
__PJSEL0             = 0x032A;
__PJSEL0_L           = 0x032A;
__PJSEL0_H           = 0x032B;
__PJSEL1             = 0x032C;
__PJSEL1_L           = 0x032C;
__PJSEL1_H           = 0x032D;
__PJSELC             = 0x0336;
__PJSELC_L           = 0x0336;
__PJSELC_H           = 0x0337;
__P1IN               = 0x0200;

__P2IN               = 0x0201;

__P2OUT              = 0x0203;

__P1OUT              = 0x0202;

__P1DIR              = 0x0204;

__P2DIR              = 0x0205;

__P1REN              = 0x0206;

__P2REN              = 0x0207;

__P1SEL0             = 0x020A;

__P2SEL0             = 0x020B;

__P1SEL1             = 0x020C;

__P2SEL1             = 0x020D;

__P1SELC             = 0x0216;

__P2SELC             = 0x0217;

__P1IES              = 0x0218;

__P2IES              = 0x0219;

__P1IE               = 0x021A;

__P2IE               = 0x021B;

__P1IFG              = 0x021C;

__P2IFG              = 0x021D;



/*****************************************************************************
 FRCTL
*****************************************************************************/
__FRCTL0             = 0x01A0;
__FRCTL0_L           = 0x01A0;
__FRCTL0_H           = 0x01A1;
__GCCTL0             = 0x01A4;
__GCCTL0_L           = 0x01A4;
__GCCTL0_H           = 0x01A5;
__GCCTL1             = 0x01A6;
__GCCTL1_L           = 0x01A6;
__GCCTL1_H           = 0x01A7;


/*****************************************************************************
 PMM
*****************************************************************************/
__PMMCTL0            = 0x0120;
__PMMCTL0_L          = 0x0120;
__PMMCTL0_H          = 0x0121;
__PMMCTL2            = 0x0124;
__PMMCTL2_L          = 0x0124;
__PMMCTL2_H          = 0x0125;
__PMMIFG             = 0x012A;
__PMMIFG_L           = 0x012A;
__PMMIFG_H           = 0x012B;
__PM5CTL0            = 0x0130;
__PM5CTL0_L          = 0x0130;
__PM5CTL0_H          = 0x0131;


/*****************************************************************************
 RTC
*****************************************************************************/
__RTCCTL             = 0x0300;
__RTCCTL_L           = 0x0300;
__RTCCTL_H           = 0x0301;
__RTCIV              = 0x0304;
__RTCIV_L            = 0x0304;
__RTCIV_H            = 0x0305;
__RTCMOD             = 0x0308;
__RTCMOD_L           = 0x0308;
__RTCMOD_H           = 0x0309;
__RTCCNT             = 0x030C;
__RTCCNT_L           = 0x030C;
__RTCCNT_H           = 0x030D;


/*****************************************************************************
 SAC0
*****************************************************************************/
__SAC0OA             = 0x0C80;
__SAC0OA_L           = 0x0C80;
__SAC0OA_H           = 0x0C81;


/*****************************************************************************
 SFR
*****************************************************************************/
__SFRIE1             = 0x0100;
__SFRIE1_L           = 0x0100;
__SFRIE1_H           = 0x0101;
__SFRIFG1            = 0x0102;
__SFRIFG1_L          = 0x0102;
__SFRIFG1_H          = 0x0103;
__SFRRPCR            = 0x0104;
__SFRRPCR_L          = 0x0104;
__SFRRPCR_H          = 0x0105;


/*****************************************************************************
 SYS
*****************************************************************************/
__SYSCTL             = 0x0140;
__SYSCTL_L           = 0x0140;
__SYSCTL_H           = 0x0141;
__SYSBSLC            = 0x0142;
__SYSBSLC_L          = 0x0142;
__SYSBSLC_H          = 0x0143;
__SYSJMBC            = 0x0146;
__SYSJMBC_L          = 0x0146;
__SYSJMBC_H          = 0x0147;
__SYSJMBI0           = 0x0148;
__SYSJMBI0_L         = 0x0148;
__SYSJMBI0_H         = 0x0149;
__SYSJMBI1           = 0x014A;
__SYSJMBI1_L         = 0x014A;
__SYSJMBI1_H         = 0x014B;
__SYSJMBO0           = 0x014C;
__SYSJMBO0_L         = 0x014C;
__SYSJMBO0_H         = 0x014D;
__SYSJMBO1           = 0x014E;
__SYSJMBO1_L         = 0x014E;
__SYSJMBO1_H         = 0x014F;
__SYSUNIV            = 0x015A;
__SYSUNIV_L          = 0x015A;
__SYSUNIV_H          = 0x015B;
__SYSSNIV            = 0x015C;
__SYSSNIV_L          = 0x015C;
__SYSSNIV_H          = 0x015D;
__SYSRSTIV           = 0x015E;
__SYSRSTIV_L         = 0x015E;
__SYSRSTIV_H         = 0x015F;
__SYSCFG0            = 0x0160;
__SYSCFG0_L          = 0x0160;
__SYSCFG0_H          = 0x0161;
__SYSCFG1            = 0x0162;
__SYSCFG1_L          = 0x0162;
__SYSCFG1_H          = 0x0163;
__SYSCFG2            = 0x0164;
__SYSCFG2_L          = 0x0164;
__SYSCFG2_H          = 0x0165;


/*****************************************************************************
 TB0
*****************************************************************************/
__TB0CTL             = 0x0380;
__TB0CTL_L           = 0x0380;
__TB0CTL_H           = 0x0381;
__TB0CCTL0           = 0x0382;
__TB0CCTL0_L         = 0x0382;
__TB0CCTL0_H         = 0x0383;
__TB0CCTL1           = 0x0384;
__TB0CCTL1_L         = 0x0384;
__TB0CCTL1_H         = 0x0385;
__TB0CCTL2           = 0x0386;
__TB0CCTL2_L         = 0x0386;
__TB0CCTL2_H         = 0x0387;
__TB0R               = 0x0390;
__TB0R_L             = 0x0390;
__TB0R_H             = 0x0391;
__TB0CCR0            = 0x0392;
__TB0CCR0_L          = 0x0392;
__TB0CCR0_H          = 0x0393;
__TB0CCR1            = 0x0394;
__TB0CCR1_L          = 0x0394;
__TB0CCR1_H          = 0x0395;
__TB0CCR2            = 0x0396;
__TB0CCR2_L          = 0x0396;
__TB0CCR2_H          = 0x0397;
__TB0EX0             = 0x03A0;
__TB0EX0_L           = 0x03A0;
__TB0EX0_H           = 0x03A1;
__TB0IV              = 0x03AE;
__TB0IV_L            = 0x03AE;
__TB0IV_H            = 0x03AF;


/*****************************************************************************
 TB1
*****************************************************************************/
__TB1CTL             = 0x03C0;
__TB1CTL_L           = 0x03C0;
__TB1CTL_H           = 0x03C1;
__TB1CCTL0           = 0x03C2;
__TB1CCTL0_L         = 0x03C2;
__TB1CCTL0_H         = 0x03C3;
__TB1CCTL1           = 0x03C4;
__TB1CCTL1_L         = 0x03C4;
__TB1CCTL1_H         = 0x03C5;
__TB1CCTL2           = 0x03C6;
__TB1CCTL2_L         = 0x03C6;
__TB1CCTL2_H         = 0x03C7;
__TB1R               = 0x03D0;
__TB1R_L             = 0x03D0;
__TB1R_H             = 0x03D1;
__TB1CCR0            = 0x03D2;
__TB1CCR0_L          = 0x03D2;
__TB1CCR0_H          = 0x03D3;
__TB1CCR1            = 0x03D4;
__TB1CCR1_L          = 0x03D4;
__TB1CCR1_H          = 0x03D5;
__TB1CCR2            = 0x03D6;
__TB1CCR2_L          = 0x03D6;
__TB1CCR2_H          = 0x03D7;
__TB1EX0             = 0x03E0;
__TB1EX0_L           = 0x03E0;
__TB1EX0_H           = 0x03E1;
__TB1IV              = 0x03EE;
__TB1IV_L            = 0x03EE;
__TB1IV_H            = 0x03EF;


/*****************************************************************************
 TRI0
*****************************************************************************/
__TRI0CTL            = 0x0F00;
__TRI0CTL_L          = 0x0F00;
__TRI0CTL_H          = 0x0F01;


/*****************************************************************************
 WDT_A
*****************************************************************************/
__WDTCTL             = 0x01CC;
__WDTCTL_L           = 0x01CC;
__WDTCTL_H           = 0x01CD;


/*****************************************************************************
 eCOMP0
*****************************************************************************/
__CPCTL0             = 0x08E0;
__CPCTL0_L           = 0x08E0;
__CPCTL0_H           = 0x08E1;
__CPCTL1             = 0x08E2;
__CPCTL1_L           = 0x08E2;
__CPCTL1_H           = 0x08E3;
__CPINT              = 0x08E6;
__CPINT_L            = 0x08E6;
__CPINT_H            = 0x08E7;
__CPIV               = 0x08E8;
__CPIV_L             = 0x08E8;
__CPIV_H             = 0x08E9;
__CPDACCTL           = 0x08F0;
__CPDACCTL_L         = 0x08F0;
__CPDACCTL_H         = 0x08F1;
__CPDACDATA          = 0x08F2;
__CPDACDATA_L        = 0x08F2;
__CPDACDATA_H        = 0x08F3;


/*****************************************************************************
 eUSCI_A0
*****************************************************************************/
__UCA0CTLW0          = 0x0500;
__UCA0CTLW0_L        = 0x0500;
__UCA0CTLW0_H        = 0x0501;
__UCA0CTLW1          = 0x0502;
__UCA0CTLW1_L        = 0x0502;
__UCA0CTLW1_H        = 0x0503;
__UCA0BRW            = 0x0506;
__UCA0BRW_L          = 0x0506;
__UCA0BRW_H          = 0x0507;
__UCA0MCTLW          = 0x0508;
__UCA0MCTLW_L        = 0x0508;
__UCA0MCTLW_H        = 0x0509;
__UCA0STATW          = 0x050A;
__UCA0STATW_L        = 0x050A;
__UCA0STATW_H        = 0x050B;
__UCA0RXBUF          = 0x050C;
__UCA0RXBUF_L        = 0x050C;
__UCA0RXBUF_H        = 0x050D;
__UCA0TXBUF          = 0x050E;
__UCA0TXBUF_L        = 0x050E;
__UCA0TXBUF_H        = 0x050F;
__UCA0ABCTL          = 0x0510;
__UCA0ABCTL_L        = 0x0510;
__UCA0ABCTL_H        = 0x0511;
__UCA0IRCTL          = 0x0512;
__UCA0IRCTL_L        = 0x0512;
__UCA0IRCTL_H        = 0x0513;
__UCA0IE             = 0x051A;
__UCA0IE_L           = 0x051A;
__UCA0IE_H           = 0x051B;
__UCA0IFG            = 0x051C;
__UCA0IFG_L          = 0x051C;
__UCA0IFG_H          = 0x051D;
__UCA0IV             = 0x051E;
__UCA0IV_L           = 0x051E;
__UCA0IV_H           = 0x051F;


/*****************************************************************************
 eUSCI_B0
*****************************************************************************/
__UCB0CTLW0          = 0x0540;
__UCB0CTLW0_L        = 0x0540;
__UCB0CTLW0_H        = 0x0541;
__UCB0CTLW1          = 0x0542;
__UCB0CTLW1_L        = 0x0542;
__UCB0CTLW1_H        = 0x0543;
__UCB0BRW            = 0x0546;
__UCB0BRW_L          = 0x0546;
__UCB0BRW_H          = 0x0547;
__UCB0STATW          = 0x0548;
__UCB0STATW_L        = 0x0548;
__UCB0STATW_H        = 0x0549;
__UCB0TBCNT          = 0x054A;
__UCB0TBCNT_L        = 0x054A;
__UCB0TBCNT_H        = 0x054B;
__UCB0RXBUF          = 0x054C;
__UCB0RXBUF_L        = 0x054C;
__UCB0RXBUF_H        = 0x054D;
__UCB0TXBUF          = 0x054E;
__UCB0TXBUF_L        = 0x054E;
__UCB0TXBUF_H        = 0x054F;
__UCB0I2COA0         = 0x0554;
__UCB0I2COA0_L       = 0x0554;
__UCB0I2COA0_H       = 0x0555;
__UCB0I2COA1         = 0x0556;
__UCB0I2COA1_L       = 0x0556;
__UCB0I2COA1_H       = 0x0557;
__UCB0I2COA2         = 0x0558;
__UCB0I2COA2_L       = 0x0558;
__UCB0I2COA2_H       = 0x0559;
__UCB0I2COA3         = 0x055A;
__UCB0I2COA3_L       = 0x055A;
__UCB0I2COA3_H       = 0x055B;
__UCB0ADDRX          = 0x055C;
__UCB0ADDRX_L        = 0x055C;
__UCB0ADDRX_H        = 0x055D;
__UCB0ADDMASK        = 0x055E;
__UCB0ADDMASK_L      = 0x055E;
__UCB0ADDMASK_H      = 0x055F;
__UCB0I2CSA          = 0x0560;
__UCB0I2CSA_L        = 0x0560;
__UCB0I2CSA_H        = 0x0561;
__UCB0IE             = 0x056A;
__UCB0IE_L           = 0x056A;
__UCB0IE_H           = 0x056B;
__UCB0IFG            = 0x056C;
__UCB0IFG_L          = 0x056C;
__UCB0IFG_H          = 0x056D;
__UCB0IV             = 0x056E;
__UCB0IV_L           = 0x056E;
__UCB0IV_H           = 0x056F;

/************************************************************
* End of Modules
************************************************************/

