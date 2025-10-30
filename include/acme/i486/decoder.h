#ifndef ACME_i486_DECODER_H
#define ACME_i486_DECODER_H

#include <acme-util/status.h>
#include <acme/i486/cpu.h>
#include <acme/i486/instruction.h>

// TODO: Confirm SEG = ES, SEG  = SS and similar in opcode map then add it []
// TODO: Opcodes determinded by bits 5,4,3 of modR/M byte: []

//  hey AI comment it better 
// will be use inside opcode table to identify instruction type
// NOTE: IMM - Immediate
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
  JCC_JO,
  JCC_JNO,
  JCC_JB,
  JCC_JNB,
  JCC_JZ,
  JCC_JNZ,
  JCC_JBE,
  JCC_JNBE,
  JCC_JS,
  JCC_JNS,
  JCC_JP,
  JCC_JNP,
  JCC_JL,
  JCC_JNL,
  JCC_JLE,
  JCC_JNLE,

  IMM_Grpl_Eb_Ib,
  IMM_Grpl_Ev_Iv,

  MOVB_AL_imm8,
  Grpl_Ev_Ib,

  TEST_Eb_Gb,
  TEST_Ev_Gv,

  XCHG_Eb_Gb,
  XCHG_Ev_Gv,

  MOV_Eb_Gb,
  MOV_Ev_Gv,
  MOV_Gb_Eb,
  MOV_Gv_Ev,
  MOV_Ew_Sw,
  LEA_Gv_M,
  MOV_Sw_Ew,
  POP_Ev,

  NOP,
  // XCHG word or double-word register with eAX
  XCHG_eAX_eCX,
  XCHG_eAX_eDX,
  XCHG_eAX_eBX,
  XCHG_eAX_eSP,
  XCHG_eAX_eBP,
  XCHG_eAX_eSI,
  XCHG_eAX_eDI,

  CBW,
  CWD,
  CALL_Ap,
  WAIT,
  PUSHF_Fv,
  POPF_Fv,
  SAHF,
  LAHF,

  MOV_AL_Ob,
  MOV_eAX_Ov,
  MOV_Ob_AL,
  MOV_Ov_eAX,

  MOVSB_Xb_Yb,
  MOVSW__D_Xv_Yv, // TODO: what is the /D find it []
  CMPSB_Xb_Yb,
  CMPSW__D_Xv_Yv, // TODO: same as above

  TEST_AL_Ib,
  TEST_eAX_Iv,

  STOSB_Yb_AL,
  STOSW__D_Yv_eAX,  // TODO: same as above
  LODSB_AL_Xb,
  LODSW__D_eAX_Xv,  // TODO: same as above

  SCASB_AL_Xb,
  SCASW__D_eAX_Xv,  // TODO: same as above

  // MOV immediate byte into byte register
  MOV_AL,
  MOV_CL,
  MOV_DL,
  MOV_BL,
  MOV_AH,
  MOV_CH,
  MOV_DH,
  MOV_BH,

  // MOV immediate word or double-word into word or double-word register
  MOV_eAX,
  MOV_eCX,
  MOV_eDX,
  MOV_eBX,
  MOV_eSP,
  MOV_eBP,
  MOV_eSI,
  MOV_eDI,
  
  Shift_Grp2_Eb_Ib,
  Shift_Grp2_Ev_Ib,
  RET_near_Iw,
  LES_Gv_Mp,
  LDS_Gv_Mp,
  MOV_Eb_Ib,
  MOV_Ev_Iv,

  ENTER_Iw_Ib,
  LEAVE,
  RET_far_Iw,

  INT_3,
  INT_Ib,
  INTO,
  IRET,

  Shift_Grp2_Eb_1,
  Shift_Grp2_Ev_1,

  Shift_Grp2_Eb_CL,
  Shift_Grp2_Ev_CL,
  
  AAM,
  AAD,
  XLAT,

  // ESC escape to coprocessor instruction set
  ESC,

  LOOPNE_Jb,
  LOOPE_Jb,
  LOOP_Jb,
  JCXZ_Jb,
  IN_AL_Ib, // TODO: check for AI or AL
  IN_eAX_Ib,
  OUT_Ib_AL,
  OUT_Ib_eAX,

  CALL_Jv,
  JMP_Jv,
  JMP_AP,
  JMP_Jb,
  IN_AL_DX,
  IN_eAX_DX,
  OUT_DX_AL,
  OUT_DX_eAX,

  LOCK,
  REPNE,
  REP_REPE, // NOTE: Check for what it is
  HLT,
  CMC,
  Unary_Grp3_Eb,
  Unary_Grp3_Ev,

  CLC,
  STC,
  CLI,
  STI,
  CLD,
  STD,

  INC__DEC_Grp4,
  INC__DEC_Grp5,

  // From here names are for two byte opcode table (first byte is 0FH)
  Grp6,
  Grp7,
  LAR_Gv_Ew,
  LSL_Gv_Ew,
  CLTS,
  INVD,
  WBINVD,

  MOV_Cd_Rd,
  MOV_Dd_Rd,
  MOV_Rd_Cd,
  MOV_Rd_Dd,
  MOV_Td_Rd,
  MOV_Rd_Td,

  // Long-displacement jump on condition (Jv)
  JV_JO,
  JV_JNO,
  JV_JB,
  JV_JNB,
  JV_JZ,
  JV_JNZ,
  JV_JBE,
  JV_JNBE,
  JV_JS,
  JV_JNS,
  JV_JP,
  JV_JNP,
  JV_JL,
  JV_JNL,
  JV_JLE,
  JV_JNLE,

  // Byte set on condition (Eb)
  Eb_SETO,
  Eb_SETNO,
  Eb_SETB,
  Eb_SETNB,
  Eb_SETZ,
  Eb_SETNZ,
  Eb_SETBE,
  Eb_SETNBE,
  Eb_SETS,
  Eb_SETNS,
  Eb_SETP,
  Eb_SETNP,
  Eb_SETL,
  Eb_SETNL,
  Eb_SETLE,
  Eb_SETNLE,

  PUSH_FS,
  POP_FS,
  BT_Ev_Gv,
  SHLD_EvGvIb,
  SHLD_EvGvCL,
  CMPXCHG_Eb_Gb,
  CMPXCHG_Ev_Gv,
  PUSH_GS,
  POP_GS,
  BTS_Ev_Gv,
  SHRD_EvGvIb,
  SHRD_EvGvCL,
  IMUL_Gv_Ev,

  LESS_Mp,
  BTR_Ev_Gv,
  LFS_Mp,
  LGS_Mp,
  MOVZX_Gv_Eb,
  MOVZX_Gv_Ev,
  Grp8_Ev_Ib,
  BTC_Ev_Gv,
  BSF_Gv_Ev,
  BSR_Gv_Ev,
  MOVSX_Gv_Eb,
  MOVSX_Gv_Ew,

  XADD_Eb_Gb,
  XADD_Ev_Gv,
  BSWAP_EAX,
  BSWAP_ECX,
  BSWAP_EDX,
  BSWAP_EBX,
  BSWAP_ESP,
  BSWAP_EBP,
  BSWAP_ESI,
  BSWAP_EDI,
  
} OpcodeName;


DecoderStatus decode(Cpu *cpu, Instruction *instruction);

#endif
