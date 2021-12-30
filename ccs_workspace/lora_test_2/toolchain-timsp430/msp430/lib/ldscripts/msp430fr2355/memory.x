/* ============================================================================ */
/* Copyright (c) 2015, Texas Instruments Incorporated                           */
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

/* This file supports MSP430FR2355 devices. */
/* Default linker script, for normal executables */

/* 1.203    (Beta-Build-Tag: #0069) */




MEMORY {
  tinyram (wx)     : ORIGIN = 0x6, LENGTH = 0x001A
  bsl0             : ORIGIN = 0x1000, LENGTH = 0x0800
  TLVMEM           : ORIGIN = 0x1A00, LENGTH = 0x0200
  BOOTCODE         : ORIGIN = 0x1C00, LENGTH = 0x0400
  ROMLIB           : ORIGIN = 0xFAC00, LENGTH = 0x5000
  bsl1             : ORIGIN = 0xFFC00, LENGTH = 0x0400
  ram (wx)         : ORIGIN = 0x2000, LENGTH = 0x1000
  infomem          : ORIGIN = 0x1800, LENGTH = 0x0200
  infoa            : ORIGIN = 0x0000, LENGTH = 0x0000
  infob            : ORIGIN = 0x0000, LENGTH = 0x0000
  infoc            : ORIGIN = 0x0000, LENGTH = 0x0000
  infod            : ORIGIN = 0x0000, LENGTH = 0x0000 
  rom (rx)         : ORIGIN = 0x8000, LENGTH = 0x7F80 /* END=0xFF7F, size 32640 */
  JTAGsignature    : ORIGIN = 0xFF80, LENGTH = 0x0004
  bslsignature     : ORIGIN = 0xFF84, LENGTH = 0x0004
  bslCONFIGURATIONsignature : ORIGIN = 0xFF88, LENGTH = 0x0002
  bslCONFIGURATION : ORIGIN = 0xFF8A, LENGTH = 0x0002
  bslICADDRESS     : ORIGIN = 0xFFA0, LENGTH = 0x0002
  vectors          : ORIGIN = 0xff80, LENGTH = 0x0080		
  ram2 (wx)        : ORIGIN = 0x0000, LENGTH = 0x0000
  far_rom          : ORIGIN = 0x00000000, LENGTH = 0x00000000
}

REGION_ALIAS("REGION_TEXT", rom);
REGION_ALIAS("REGION_DATA", ram);
REGION_ALIAS("REGION_FAR_ROM", far_rom); /* Legacy name, no longer used */
REGION_ALIAS("REGION_FAR_TEXT", far_rom);
REGION_ALIAS("REGION_FAR_DATA", ram2);
PROVIDE (__info_segment_size = 0x80);
PROVIDE (__infod = 0x1800);
PROVIDE (__infoc = 0x1880);
PROVIDE (__infob = 0x1900);
PROVIDE (__infoa = 0x1980); 

