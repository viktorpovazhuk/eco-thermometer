MEMORY {
  sfr              : ORIGIN = 0x0000, LENGTH = 0x0010 /* END=0x0010, size 16 */
  peripheral_8bit  : ORIGIN = 0x0010, LENGTH = 0x00f0 /* END=0x0100, size 240 */
  peripheral_16bit : ORIGIN = 0x0100, LENGTH = 0x0100 /* END=0x0200, size 256 */
  bsl              : ORIGIN = 0x1000, LENGTH = 0x0400 /* END=0x1400, size 1K as 1 1024-byte segments */
  ram (wx)         : ORIGIN = 0x2000, LENGTH = 0x0400 /* END=0x2400, size 1K */
  rom (rx)         : ORIGIN = 0xf100, LENGTH = 0x0e80 /* END=0xff80, size 3712 */
  signature        : ORIGIN = 0xff80, LENGTH = 0x0008 /* END=0xff88, size 8 as 1 8-byte segments */
  vectors          : ORIGIN = 0xff80, LENGTH = 0x0080 /* END=0x10000, size 128 as 64 2-byte segments */
  /* Remaining banks are absent */
  infomem          : ORIGIN = 0x0000, LENGTH = 0x0000
  infoa            : ORIGIN = 0x0000, LENGTH = 0x0000
  infob            : ORIGIN = 0x0000, LENGTH = 0x0000
  infoc            : ORIGIN = 0x0000, LENGTH = 0x0000
  infod            : ORIGIN = 0x0000, LENGTH = 0x0000
  ram2 (wx)        : ORIGIN = 0x0000, LENGTH = 0x0000
  ram_mirror (wx)  : ORIGIN = 0x0000, LENGTH = 0x0000
  tinyram (wx)     : ORIGIN = 0x0000, LENGTH = 0x0000
  usbram (wx)      : ORIGIN = 0x0000, LENGTH = 0x0000
  far_rom          : ORIGIN = 0x00000000, LENGTH = 0x00000000
}
REGION_ALIAS("REGION_TEXT", rom);
REGION_ALIAS("REGION_DATA", ram);
REGION_ALIAS("REGION_FAR_ROM", far_rom); /* Legacy name, no longer used */
REGION_ALIAS("REGION_FAR_TEXT", far_rom);
REGION_ALIAS("REGION_FAR_DATA", ram2);
