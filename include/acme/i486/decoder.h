#ifndef ACME_i486_DECODER_H
#define ACME_i486_DECODER_H

// Only first byte of opcode primary opcode
typedef enum Opcodes {

  AAA__x37 = 0x37,
  AAD__xD5 = 0xD5,
  AAD2__x0A = 0x0A,
  AAM__xD4 = 0xD4,
  AAM2__x0A = 0x0A,
  AAS__x3F = 0x3F,

  // ADC - Add with carry

  ADC_ib__x14 = 0x14,
  ADC_iw_or_id__x15 = 0x15,
  ADC_2_ib__x80 = 0x80,
  ADC_2_iw_or_id__x81 = 0x81,
  ADC_2_ib_rm16_or_32__x83 = 0x83,

  ADC_r_rm8_r8__x10__x10 = 0x10,
  ADC_r_rm_r16_or_32__x11 = 0x11,
  ADC_r_r8_rm8__x12 = 0x12,
  ADC_r_r_rm16_or_32__x13 = 0x13,

  // ADD - Add

  ADD_ib__x04 = 0x04,
  ADD_iw_or_id__x05 = 0x05,
  ADD_0_ib_rm8__x80 = 0x80,
  ADD_iw_or_id_rm16_or_32__x81 = 0x81,
  ADD_0_ib_rm16_or_32__x83 = 0x83,
  ADD_r_rm8_r8__x00 = 0x00,
  ADD_r_rm16_or_32__x01 = 0x01,
  ADD_r_r8_rm8__x02 = 0x02,
  ADD_r_r_rm16_or_32__x03 = 0x03,

} Opcodes;
#endif // !A
