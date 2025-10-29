#ifndef ACME_i486_DECODER_H
#define ACME_i486_DECODER_H

#include <acme-util/status.h>
#include <acme/i486/cpu.h>
#include <acme/i486/instruction.h>

// TODO: Confirm SEG = ES, SEG  = SS and similar in opcode map then add it []

//  hey AI comment it better 
// will be use inside opcode table to identify instruction type
typedef enum OpcodeName {
  ADD_Eb_Gb,
  ADD_Ev_Gv,
  ADD_Gb_Eb,
  ADD_Gv_Ev,
  ADD_AL_Ib,
  ADD_eAX_Iv,

  PUSH_ES,
  POP_ES,

  OR_Eb_Gb,
  OR_Ev_Gv,
  OR_Gb_Eb,
  OR_Gv_Ev,
  OR_AL_Ib,
  OR_eAX_Iv,

  PUSH_CS,
  ESCAPE_2_byte,

  ADC_Eb_Gb,
  ADC_Ev_Gv,
  ADC_Gb_Eb,
  ADC_Gv_Ev,
  ADC_AL_Ib,
  ADC_eAX_Iv,

  PUSH_SS,
  POP_SS,

  SBB_Eb_Gb,
  SBB_Ev_Gv,
  SBB_Gb_Eb,
  SBB_Gv_Ev,
  SBB_AL_Ib,
  SBB_eAX_Iv,

  PUSH_DS,
  POP_DS,

  AND_Eb_Gb,
  AND_Ev_Gv,
  AND_Gb_Eb,
  AND_Gv_Ev,
  AND_AL_Ib,
  AND_eAX_Iv,

  // NOTE: space for SEG = ES
  DAA,
  SUB_Eb_Gb,
  SUB_Ev_Gv,
  SUB_Gb_Eb,
  SUB_Gv_Ev,
  SUB_AL_Ib,
  SUB_eAX_Iv,

  // NOTE: space for SEG = CS
  DAS,
  XOR_Eb_Gb,
  XOR_Ev_Gv,
  XOR_Gb_Eb,
  XOR_Gb_Ev,
  XOR_AL_Ib,
  XOR_eAX_Iv,
  
  // NOTE: space for SEG = SS
  AAA,
  CMP_Eb_Gb,
  CMP_Ev_Gv,
  CMP_Gb_Eb,
  CMP_Gv_Ev,
  CMP_AL_Ib,
  CMP_eAX_Iv,

  // NOTE: space for SEG = DS
  AAS,

  // increment general purpose registers
  INC_eAX,
  INC_eCX,
  INC_eDX,
  INC_eBX,
  INC_eSP,
  INC_eBP,
  INC_eSI,
  INC_eDI,

  // decrement general purpose registers
  DEC_eAX,
  DEC_eCX,
  DEC_eDX,
  DEC_eBX,
  DEC_eSP,
  DEC_eBP,
  DEC_eSI,
  DEC_eDI,

  // PUSH general register
  PUSH_eAX,
  PUSH_eCX,
  PUSH_eDX,
  PUSH_eBX,
  PUSH_eSP,
  PUSH_eBP,
  PUSH_eSI,
  PUSH_eDI,

  // POP into general register
  POP_eAX,
  POP_eCX,
  POP_eDX,
  POP_eBX,
  POP_eSP,
  POP_eBP,
  POP_eSI,
  POP_eDI,

  PUSHA,
  POPA,
  BOUND_Gv_Ma,
  ARPL_Ew_Rw,
  // NOTE: Space for SEG = FS
  // NOTE: Space for SEG = GS
  PREFIX_Operand_Size,
  PREFIX_Address_Size,

  PUSH_Iv,
  IMUL_Gv_Ev_Iv,
  PUSH_Ib,
  IMUL_GvEvIb,
  INSB_Yb_DX,
  INSW__D_Yv_DX,  // TODO: what is the INSW/D find it []
  OUTSB_DX_Xb,
  OUTSW__D_DX_Xv,  // TODO: what is the OUTSW/D find it []

  // Short-displacement jump on condition (Jb)

} OpcodeName;


DecoderStatus decode(Cpu *cpu, Instruction *instruction);

#endif
