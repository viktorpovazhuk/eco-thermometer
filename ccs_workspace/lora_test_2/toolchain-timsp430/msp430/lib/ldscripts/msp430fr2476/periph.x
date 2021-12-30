/* ============================================================================ */
/* Copyright (c) 2018, Texas Instruments Incorporated                           */
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

/* This file supports MSP430FR2476 devices. */

/* 1.207 */

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
__PBIN               = 0x0220;
__PBIN_L             = 0x0220;
__PBIN_H             = 0x0221;
__PBOUT              = 0x0222;
__PBOUT_L            = 0x0222;
__PBOUT_H            = 0x0223;
__PBDIR              = 0x0224;
__PBDIR_L            = 0x0224;
__PBDIR_H            = 0x0225;
__PBREN              = 0x0226;
__PBREN_L            = 0x0226;
__PBREN_H            = 0x0227;
__PBSEL0             = 0x022A;
__PBSEL0_L           = 0x022A;
__PBSEL0_H           = 0x022B;
__PBSEL1             = 0x022C;
__PBSEL1_L           = 0x022C;
__PBSEL1_H           = 0x022D;
__P3IV               = 0x022E;
__P3IV_L             = 0x022E;
__P3IV_H             = 0x022F;
__PBSELC             = 0x0236;
__PBSELC_L           = 0x0236;
__PBSELC_H           = 0x0237;
__PBIES              = 0x0238;
__PBIES_L            = 0x0238;
__PBIES_H            = 0x0239;
__PBIE               = 0x023A;
__PBIE_L             = 0x023A;
__PBIE_H             = 0x023B;
__PBIFG              = 0x023C;
__PBIFG_L            = 0x023C;
__PBIFG_H            = 0x023D;
__P4IV               = 0x023E;
__P4IV_L             = 0x023E;
__P4IV_H             = 0x023F;
__PCIN               = 0x0240;
__PCIN_L             = 0x0240;
__PCIN_H             = 0x0241;
__PCOUT              = 0x0242;
__PCOUT_L            = 0x0242;
__PCOUT_H            = 0x0243;
__PCDIR              = 0x0244;
__PCDIR_L            = 0x0244;
__PCDIR_H            = 0x0245;
__PCREN              = 0x0246;
__PCREN_L            = 0x0246;
__PCREN_H            = 0x0247;
__PCSEL0             = 0x024A;
__PCSEL0_L           = 0x024A;
__PCSEL0_H           = 0x024B;
__PCSEL1             = 0x024C;
__PCSEL1_L           = 0x024C;
__PCSEL1_H           = 0x024D;
__P5IV               = 0x024E;
__P5IV_L             = 0x024E;
__P5IV_H             = 0x024F;
__PCSELC             = 0x0256;
__PCSELC_L           = 0x0256;
__PCSELC_H           = 0x0257;
__PCIES              = 0x0258;
__PCIES_L            = 0x0258;
__PCIES_H            = 0x0259;
__PCIE               = 0x025A;
__PCIE_L             = 0x025A;
__PCIE_H             = 0x025B;
__PCIFG              = 0x025C;
__PCIFG_L            = 0x025C;
__PCIFG_H            = 0x025D;
__P6IV               = 0x025E;
__P6IV_L             = 0x025E;
__P6IV_H             = 0x025F;
__PDIN               = 0x0260;
__PDIN_L             = 0x0260;
__PDIN_H             = 0x0261;
__PDOUT              = 0x0262;
__PDOUT_L            = 0x0262;
__PDOUT_H            = 0x0263;
__PDDIR              = 0x0264;
__PDDIR_L            = 0x0264;
__PDDIR_H            = 0x0265;
__PDREN              = 0x0266;
__PDREN_L            = 0x0266;
__PDREN_H            = 0x0267;
__PDSEL0             = 0x026A;
__PDSEL0_L           = 0x026A;
__PDSEL0_H           = 0x026B;
__PDSEL1             = 0x026C;
__PDSEL1_L           = 0x026C;
__PDSEL1_H           = 0x026D;
__PDSELC             = 0x0276;
__PDSELC_L           = 0x0276;
__PDSELC_H           = 0x0277;
__PDIES              = 0x0278;
__PDIES_L            = 0x0278;
__PDIES_H            = 0x0279;
__PDIE               = 0x027A;
__PDIE_L             = 0x027A;
__PDIE_H             = 0x027B;
__PDIFG              = 0x027C;
__PDIFG_L            = 0x027C;
__PDIFG_H            = 0x027D;
__PEIN               = 0x0280;
__PEIN_L             = 0x0280;
__PEIN_H             = 0x0281;
__PEOUT              = 0x0282;
__PEOUT_L            = 0x0282;
__PEOUT_H            = 0x0283;
__PEDIR              = 0x0284;
__PEDIR_L            = 0x0284;
__PEDIR_H            = 0x0285;
__PEREN              = 0x0286;
__PEREN_L            = 0x0286;
__PEREN_H            = 0x0287;
__PESEL0             = 0x028A;
__PESEL0_L           = 0x028A;
__PESEL0_H           = 0x028B;
__PESEL1             = 0x028C;
__PESEL1_L           = 0x028C;
__PESEL1_H           = 0x028D;
__PESELC             = 0x0296;
__PESELC_L           = 0x0296;
__PESELC_H           = 0x0297;
__PEIES              = 0x0298;
__PEIES_L            = 0x0298;
__PEIES_H            = 0x0299;
__PEIE               = 0x029A;
__PEIE_L             = 0x029A;
__PEIE_H             = 0x029B;
__PEIFG              = 0x029C;
__PEIFG_L            = 0x029C;
__PEIFG_H            = 0x029D;
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

__P3IN               = 0x0220;

__P4IN               = 0x0221;

__P3OUT              = 0x0222;

__P4OUT              = 0x0223;

__P3DIR              = 0x0224;

__P4DIR              = 0x0225;

__P3REN              = 0x0226;

__P4REN              = 0x0227;

__P4SEL0             = 0x022B;

__P3SEL0             = 0x022A;

__P3SEL1             = 0x022C;

__P4SEL1             = 0x022D;

__P3SELC             = 0x0236;

__P4SELC             = 0x0237;

__P3IES              = 0x0238;

__P4IES              = 0x0239;

__P3IE               = 0x023A;

__P4IE               = 0x023B;

__P3IFG              = 0x023C;

__P4IFG              = 0x023D;

__P5IN               = 0x0240;

__P6IN               = 0x0241;

__P5OUT              = 0x0242;

__P6OUT              = 0x0243;

__P5DIR              = 0x0244;

__P6DIR              = 0x0245;

__P5REN              = 0x0246;

__P6REN              = 0x0247;

__P5SEL0             = 0x024A;

__P6SEL0             = 0x024B;

__P5SEL1             = 0x024C;

__P6SEL1             = 0x024D;

__P5SELC             = 0x0256;

__P6SELC             = 0x0257;

__P5IES              = 0x0258;

__P6IES              = 0x0259;

__P5IE               = 0x025A;

__P6IE               = 0x025B;

__P5IFG              = 0x025C;

__P6IFG              = 0x025D;

__P7IN               = 0x0260;

__P8IN               = 0x0261;

__P7OUT              = 0x0262;

__P8OUT              = 0x0263;

__P7DIR              = 0x0264;

__P8DIR              = 0x0265;

__P7REN              = 0x0266;

__P8REN              = 0x0267;

__P7SEL0             = 0x026A;

__P8SEL0             = 0x026B;

__P7SEL1             = 0x026C;

__P8SEL1             = 0x026D;

__P7SELC             = 0x0276;

__P8SELC             = 0x0277;

__P7IES              = 0x0278;

__P8IES              = 0x0279;

__P7IE               = 0x027A;

__P8IE               = 0x027B;

__P7IFG              = 0x027C;

__P8IFG              = 0x027D;

__P9IN               = 0x0280;

__P10IN              = 0x0281;

__P9OUT              = 0x0282;

__P10OUT             = 0x0283;

__P9DIR              = 0x0284;

__P10DIR             = 0x0285;

__P9REN              = 0x0286;

__P10REN             = 0x0287;

__P9SEL0             = 0x028A;

__P10SEL0            = 0x028B;

__P9SEL1             = 0x028C;

__P10SEL1            = 0x028D;

__P9SELC             = 0x0296;

__P10SELC            = 0x0297;

__P9IES              = 0x0298;

__P10IES             = 0x0299;

__P9IE               = 0x029A;

__P10IE              = 0x029B;

__P10IFG             = 0x029D;

__P9IFG              = 0x029C;



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
 MPY32
*****************************************************************************/
__MPY                = 0x04C0;
__MPY_L              = 0x04C0;
__MPY_H              = 0x04C1;
__MPYS               = 0x04C2;
__MPYS_L             = 0x04C2;
__MPYS_H             = 0x04C3;
__MAC                = 0x04C4;
__MAC_L              = 0x04C4;
__MAC_H              = 0x04C5;
__MACS               = 0x04C6;
__MACS_L             = 0x04C6;
__MACS_H             = 0x04C7;
__OP2                = 0x04C8;
__OP2_L              = 0x04C8;
__OP2_H              = 0x04C9;
__RESLO              = 0x04CA;
__RESLO_L            = 0x04CA;
__RESLO_H            = 0x04CB;
__RESHI              = 0x04CC;
__RESHI_L            = 0x04CC;
__RESHI_H            = 0x04CD;
__SUMEXT             = 0x04CE;
__SUMEXT_L           = 0x04CE;
__SUMEXT_H           = 0x04CF;
__MPY32L             = 0x04D0;
__MPY32L_L           = 0x04D0;
__MPY32L_H           = 0x04D1;
__MPY32H             = 0x04D2;
__MPY32H_L           = 0x04D2;
__MPY32H_H           = 0x04D3;
__MPYS32L            = 0x04D4;
__MPYS32L_L          = 0x04D4;
__MPYS32L_H          = 0x04D5;
__MPYS32H            = 0x04D6;
__MPYS32H_L          = 0x04D6;
__MPYS32H_H          = 0x04D7;
__MAC32L             = 0x04D8;
__MAC32L_L           = 0x04D8;
__MAC32L_H           = 0x04D9;
__MAC32H             = 0x04DA;
__MAC32H_L           = 0x04DA;
__MAC32H_H           = 0x04DB;
__MACS32L            = 0x04DC;
__MACS32L_L          = 0x04DC;
__MACS32L_H          = 0x04DD;
__MACS32H            = 0x04DE;
__MACS32H_L          = 0x04DE;
__MACS32H_H          = 0x04DF;
__OP2L               = 0x04E0;
__OP2L_L             = 0x04E0;
__OP2L_H             = 0x04E1;
__OP2H               = 0x04E2;
__OP2H_L             = 0x04E2;
__OP2H_H             = 0x04E3;
__RES0               = 0x04E4;
__RES0_L             = 0x04E4;
__RES0_H             = 0x04E5;
__RES1               = 0x04E6;
__RES1_L             = 0x04E6;
__RES1_H             = 0x04E7;
__RES2               = 0x04E8;
__RES2_L             = 0x04E8;
__RES2_H             = 0x04E9;
__RES3               = 0x04EA;
__RES3_L             = 0x04EA;
__RES3_H             = 0x04EB;
__MPY32CTL0          = 0x04EC;
__MPY32CTL0_L        = 0x04EC;
__MPY32CTL0_H        = 0x04ED;


/*****************************************************************************
 PMM
*****************************************************************************/
__PMMCTL0            = 0x0120;
__PMMCTL0_L          = 0x0120;
__PMMCTL0_H          = 0x0121;
__PMMCTL1            = 0x0122;
__PMMCTL1_L          = 0x0122;
__PMMCTL1_H          = 0x0123;
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
__SYSCFG3            = 0x0166;
__SYSCFG3_L          = 0x0166;
__SYSCFG3_H          = 0x0167;


/*****************************************************************************
 TA0
*****************************************************************************/
__TA0CTL             = 0x0380;
__TA0CTL_L           = 0x0380;
__TA0CTL_H           = 0x0381;
__TA0CCTL0           = 0x0382;
__TA0CCTL0_L         = 0x0382;
__TA0CCTL0_H         = 0x0383;
__TA0CCTL1           = 0x0384;
__TA0CCTL1_L         = 0x0384;
__TA0CCTL1_H         = 0x0385;
__TA0CCTL2           = 0x0386;
__TA0CCTL2_L         = 0x0386;
__TA0CCTL2_H         = 0x0387;
__TA0R               = 0x0390;
__TA0R_L             = 0x0390;
__TA0R_H             = 0x0391;
__TA0CCR0            = 0x0392;
__TA0CCR0_L          = 0x0392;
__TA0CCR0_H          = 0x0393;
__TA0CCR1            = 0x0394;
__TA0CCR1_L          = 0x0394;
__TA0CCR1_H          = 0x0395;
__TA0CCR2            = 0x0396;
__TA0CCR2_L          = 0x0396;
__TA0CCR2_H          = 0x0397;
__TA0EX0             = 0x03A0;
__TA0EX0_L           = 0x03A0;
__TA0EX0_H           = 0x03A1;
__TA0IV              = 0x03AE;
__TA0IV_L            = 0x03AE;
__TA0IV_H            = 0x03AF;


/*****************************************************************************
 TA1
*****************************************************************************/
__TA1CTL             = 0x03C0;
__TA1CTL_L           = 0x03C0;
__TA1CTL_H           = 0x03C1;
__TA1CCTL0           = 0x03C2;
__TA1CCTL0_L         = 0x03C2;
__TA1CCTL0_H         = 0x03C3;
__TA1CCTL1           = 0x03C4;
__TA1CCTL1_L         = 0x03C4;
__TA1CCTL1_H         = 0x03C5;
__TA1CCTL2           = 0x03C6;
__TA1CCTL2_L         = 0x03C6;
__TA1CCTL2_H         = 0x03C7;
__TA1R               = 0x03D0;
__TA1R_L             = 0x03D0;
__TA1R_H             = 0x03D1;
__TA1CCR0            = 0x03D2;
__TA1CCR0_L          = 0x03D2;
__TA1CCR0_H          = 0x03D3;
__TA1CCR1            = 0x03D4;
__TA1CCR1_L          = 0x03D4;
__TA1CCR1_H          = 0x03D5;
__TA1CCR2            = 0x03D6;
__TA1CCR2_L          = 0x03D6;
__TA1CCR2_H          = 0x03D7;
__TA1EX0             = 0x03E0;
__TA1EX0_L           = 0x03E0;
__TA1EX0_H           = 0x03E1;
__TA1IV              = 0x03EE;
__TA1IV_L            = 0x03EE;
__TA1IV_H            = 0x03EF;


/*****************************************************************************
 TA2
*****************************************************************************/
__TA2CTL             = 0x0400;
__TA2CTL_L           = 0x0400;
__TA2CTL_H           = 0x0401;
__TA2CCTL0           = 0x0402;
__TA2CCTL0_L         = 0x0402;
__TA2CCTL0_H         = 0x0403;
__TA2CCTL1           = 0x0404;
__TA2CCTL1_L         = 0x0404;
__TA2CCTL1_H         = 0x0405;
__TA2CCTL2           = 0x0406;
__TA2CCTL2_L         = 0x0406;
__TA2CCTL2_H         = 0x0407;
__TA2R               = 0x0410;
__TA2R_L             = 0x0410;
__TA2R_H             = 0x0411;
__TA2CCR0            = 0x0412;
__TA2CCR0_L          = 0x0412;
__TA2CCR0_H          = 0x0413;
__TA2CCR1            = 0x0414;
__TA2CCR1_L          = 0x0414;
__TA2CCR1_H          = 0x0415;
__TA2CCR2            = 0x0416;
__TA2CCR2_L          = 0x0416;
__TA2CCR2_H          = 0x0417;
__TA2EX0             = 0x0420;
__TA2EX0_L           = 0x0420;
__TA2EX0_H           = 0x0421;
__TA2IV              = 0x042E;
__TA2IV_L            = 0x042E;
__TA2IV_H            = 0x042F;


/*****************************************************************************
 TA3
*****************************************************************************/
__TA3CTL             = 0x0440;
__TA3CTL_L           = 0x0440;
__TA3CTL_H           = 0x0441;
__TA3CCTL0           = 0x0442;
__TA3CCTL0_L         = 0x0442;
__TA3CCTL0_H         = 0x0443;
__TA3CCTL1           = 0x0444;
__TA3CCTL1_L         = 0x0444;
__TA3CCTL1_H         = 0x0445;
__TA3CCTL2           = 0x0446;
__TA3CCTL2_L         = 0x0446;
__TA3CCTL2_H         = 0x0447;
__TA3R               = 0x0450;
__TA3R_L             = 0x0450;
__TA3R_H             = 0x0451;
__TA3CCR0            = 0x0452;
__TA3CCR0_L          = 0x0452;
__TA3CCR0_H          = 0x0453;
__TA3CCR1            = 0x0454;
__TA3CCR1_L          = 0x0454;
__TA3CCR1_H          = 0x0455;
__TA3CCR2            = 0x0456;
__TA3CCR2_L          = 0x0456;
__TA3CCR2_H          = 0x0457;
__TA3EX0             = 0x0460;
__TA3EX0_L           = 0x0460;
__TA3EX0_H           = 0x0461;
__TA3IV              = 0x046E;
__TA3IV_L            = 0x046E;
__TA3IV_H            = 0x046F;


/*****************************************************************************
 TB0
*****************************************************************************/
__TB0CTL             = 0x0480;
__TB0CTL_L           = 0x0480;
__TB0CTL_H           = 0x0481;
__TB0CCTL0           = 0x0482;
__TB0CCTL0_L         = 0x0482;
__TB0CCTL0_H         = 0x0483;
__TB0CCTL1           = 0x0484;
__TB0CCTL1_L         = 0x0484;
__TB0CCTL1_H         = 0x0485;
__TB0CCTL2           = 0x0486;
__TB0CCTL2_L         = 0x0486;
__TB0CCTL2_H         = 0x0487;
__TB0CCTL3           = 0x0488;
__TB0CCTL3_L         = 0x0488;
__TB0CCTL3_H         = 0x0489;
__TB0CCTL4           = 0x048A;
__TB0CCTL4_L         = 0x048A;
__TB0CCTL4_H         = 0x048B;
__TB0CCTL5           = 0x048C;
__TB0CCTL5_L         = 0x048C;
__TB0CCTL5_H         = 0x048D;
__TB0CCTL6           = 0x048E;
__TB0CCTL6_L         = 0x048E;
__TB0CCTL6_H         = 0x048F;
__TB0R               = 0x0490;
__TB0R_L             = 0x0490;
__TB0R_H             = 0x0491;
__TB0CCR0            = 0x0492;
__TB0CCR0_L          = 0x0492;
__TB0CCR0_H          = 0x0493;
__TB0CCR1            = 0x0494;
__TB0CCR1_L          = 0x0494;
__TB0CCR1_H          = 0x0495;
__TB0CCR2            = 0x0496;
__TB0CCR2_L          = 0x0496;
__TB0CCR2_H          = 0x0497;
__TB0CCR3            = 0x0498;
__TB0CCR3_L          = 0x0498;
__TB0CCR3_H          = 0x0499;
__TB0CCR4            = 0x049A;
__TB0CCR4_L          = 0x049A;
__TB0CCR4_H          = 0x049B;
__TB0CCR5            = 0x049C;
__TB0CCR5_L          = 0x049C;
__TB0CCR5_H          = 0x049D;
__TB0CCR6            = 0x049E;
__TB0CCR6_L          = 0x049E;
__TB0CCR6_H          = 0x049F;
__TB0EX0             = 0x04A0;
__TB0EX0_L           = 0x04A0;
__TB0EX0_H           = 0x04A1;
__TB0IV              = 0x04AE;
__TB0IV_L            = 0x04AE;
__TB0IV_H            = 0x04AF;


/*****************************************************************************
 WDT_A
*****************************************************************************/
__WDTCTL             = 0x01CC;
__WDTCTL_L           = 0x01CC;
__WDTCTL_H           = 0x01CD;


/*****************************************************************************
 eCOMP0
*****************************************************************************/
__CP0CTL0            = 0x08E0;
__CP0CTL0_L          = 0x08E0;
__CP0CTL0_H          = 0x08E1;
__CP0CTL1            = 0x08E2;
__CP0CTL1_L          = 0x08E2;
__CP0CTL1_H          = 0x08E3;
__CP0INT             = 0x08E6;
__CP0INT_L           = 0x08E6;
__CP0INT_H           = 0x08E7;
__CP0IV              = 0x08E8;
__CP0IV_L            = 0x08E8;
__CP0IV_H            = 0x08E9;
__CP0DACCTL          = 0x08F0;
__CP0DACCTL_L        = 0x08F0;
__CP0DACCTL_H        = 0x08F1;
__CP0DACDATA         = 0x08F2;
__CP0DACDATA_L       = 0x08F2;
__CP0DACDATA_H       = 0x08F3;


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
 eUSCI_A1
*****************************************************************************/
__UCA1CTLW0          = 0x0520;
__UCA1CTLW0_L        = 0x0520;
__UCA1CTLW0_H        = 0x0521;
__UCA1CTLW1          = 0x0522;
__UCA1CTLW1_L        = 0x0522;
__UCA1CTLW1_H        = 0x0523;
__UCA1BRW            = 0x0526;
__UCA1BRW_L          = 0x0526;
__UCA1BRW_H          = 0x0527;
__UCA1MCTLW          = 0x0528;
__UCA1MCTLW_L        = 0x0528;
__UCA1MCTLW_H        = 0x0529;
__UCA1STATW          = 0x052A;
__UCA1STATW_L        = 0x052A;
__UCA1STATW_H        = 0x052B;
__UCA1RXBUF          = 0x052C;
__UCA1RXBUF_L        = 0x052C;
__UCA1RXBUF_H        = 0x052D;
__UCA1TXBUF          = 0x052E;
__UCA1TXBUF_L        = 0x052E;
__UCA1TXBUF_H        = 0x052F;
__UCA1ABCTL          = 0x0530;
__UCA1ABCTL_L        = 0x0530;
__UCA1ABCTL_H        = 0x0531;
__UCA1IRCTL          = 0x0532;
__UCA1IRCTL_L        = 0x0532;
__UCA1IRCTL_H        = 0x0533;
__UCA1IE             = 0x053A;
__UCA1IE_L           = 0x053A;
__UCA1IE_H           = 0x053B;
__UCA1IFG            = 0x053C;
__UCA1IFG_L          = 0x053C;
__UCA1IFG_H          = 0x053D;
__UCA1IV             = 0x053E;
__UCA1IV_L           = 0x053E;
__UCA1IV_H           = 0x053F;


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


/*****************************************************************************
 eUSCI_B1
*****************************************************************************/
__UCB1CTLW0          = 0x0580;
__UCB1CTLW0_L        = 0x0580;
__UCB1CTLW0_H        = 0x0581;
__UCB1CTLW1          = 0x0582;
__UCB1CTLW1_L        = 0x0582;
__UCB1CTLW1_H        = 0x0583;
__UCB1BRW            = 0x0586;
__UCB1BRW_L          = 0x0586;
__UCB1BRW_H          = 0x0587;
__UCB1STATW          = 0x0588;
__UCB1STATW_L        = 0x0588;
__UCB1STATW_H        = 0x0589;
__UCB1TBCNT          = 0x058A;
__UCB1TBCNT_L        = 0x058A;
__UCB1TBCNT_H        = 0x058B;
__UCB1RXBUF          = 0x058C;
__UCB1RXBUF_L        = 0x058C;
__UCB1RXBUF_H        = 0x058D;
__UCB1TXBUF          = 0x058E;
__UCB1TXBUF_L        = 0x058E;
__UCB1TXBUF_H        = 0x058F;
__UCB1I2COA0         = 0x0594;
__UCB1I2COA0_L       = 0x0594;
__UCB1I2COA0_H       = 0x0595;
__UCB1I2COA1         = 0x0596;
__UCB1I2COA1_L       = 0x0596;
__UCB1I2COA1_H       = 0x0597;
__UCB1I2COA2         = 0x0598;
__UCB1I2COA2_L       = 0x0598;
__UCB1I2COA2_H       = 0x0599;
__UCB1I2COA3         = 0x059A;
__UCB1I2COA3_L       = 0x059A;
__UCB1I2COA3_H       = 0x059B;
__UCB1ADDRX          = 0x059C;
__UCB1ADDRX_L        = 0x059C;
__UCB1ADDRX_H        = 0x059D;
__UCB1ADDMASK        = 0x059E;
__UCB1ADDMASK_L      = 0x059E;
__UCB1ADDMASK_H      = 0x059F;
__UCB1I2CSA          = 0x05A0;
__UCB1I2CSA_L        = 0x05A0;
__UCB1I2CSA_H        = 0x05A1;
__UCB1IE             = 0x05AA;
__UCB1IE_L           = 0x05AA;
__UCB1IE_H           = 0x05AB;
__UCB1IFG            = 0x05AC;
__UCB1IFG_L          = 0x05AC;
__UCB1IFG_H          = 0x05AD;
__UCB1IV             = 0x05AE;
__UCB1IV_L           = 0x05AE;
__UCB1IV_H           = 0x05AF;

/************************************************************
* End of Modules
************************************************************/

