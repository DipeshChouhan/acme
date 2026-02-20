/**
 * @file
 * @brief Defines x86 opcode maps for one-byte, two-byte, and grouped opcodes.
 *
 * These maps are essential for the i486 instruction decoder,
 * providing a structured lookup for instruction decoding based on opcode bytes.
 */
#include <acme/i486/decoder.h>

/**
 * @brief Lookup table for one-byte x86 opcodes.
 *
 * This 16x16 array maps the first byte of an opcode to its corresponding
 * instruction. The row index represents the most significant nibble (bits 7-4)
 * of the opcode byte, and the column index represents the least significant
 * nibble (bits 3-0).
 *
 * Each entry is a symbolic constant (e.g., ADD_Eb_Gb) representing a specific
 * x86 instruction. The order of these opcodes is critical for correct decoding.
 */

typedef struct {
    int opcode;
    int has_modrm;
} OpcodeEntry;

#define ESCAPE_2_byte_opcode_table 0
OpcodeEntry one_byte_opcodemap[16][16] = {
    // Row 0
    {{ADD_Eb_Gb, 1}, {ADD_Ev_Gv, 1}, {ADD_Gb_Eb, 1}, {ADD_Gv_Ev, 1}, {ADD_AL_Ib, 0}, {ADD_eAX_Iv, 0}, {PUSH_ES, 0}, {POP_ES, 0},
     {OR_Eb_Gb, 1}, {OR_Ev_Gv, 1}, {OR_Gb_Eb, 1}, {OR_Gv_Ev, 1}, {OR_AL_Ib, 0}, {OR_eAX_Iv, 0}, {PUSH_CS, 0}, {ESCAPE_2_byte_opcode_table, 0}},

    // Row 1
    {{ADC_Eb_Gb, 1}, {ADC_Ev_Gv, 1}, {ADC_Gb_Eb, 1}, {ADC_Gv_Ev, 1}, {ADC_AL_Ib, 0}, {ADC_eAX_Iv, 0}, {PUSH_SS, 0}, {POP_SS, 0},
     {SBB_Eb_Gb, 1}, {SBB_Ev_Gv, 1}, {SBB_Gb_Eb, 1}, {SBB_Gv_Ev, 1}, {SBB_AL_Ib, 0}, {SBB_eAX_Iv, 0}, {PUSH_DS, 0}, {POP_DS, 0}},

    // Row 2
    {{AND_Eb_Gb, 1}, {AND_Ev_Gv, 1}, {AND_Gb_Eb, 1}, {AND_Gv_Ev, 1}, {AND_AL_Ib, 0}, {AND_eAX_Iv, 0}, {PREFIX_SegOverride_ES, 0}, {DAA, 0},
     {SUB_Eb_Gb, 1}, {SUB_Ev_Gv, 1}, {SUB_Gb_Eb, 1}, {SUB_Gv_Ev, 1}, {SUB_AL_Ib, 0}, {SUB_eAX_Iv, 0}, {PREFIX_SegOverride_CS, 0}, {DAS, 0}},

    // Row 3
    {{XOR_Eb_Gb, 1}, {XOR_Ev_Gv, 1}, {XOR_Gb_Eb, 1}, {XOR_Gv_Ev, 1}, {XOR_AL_Ib, 0}, {XOR_eAX_Iv, 0}, {PREFIX_SegOverride_SS, 0}, {AAA, 0},
     {CMP_Eb_Gb, 1}, {CMP_Ev_Gv, 1}, {CMP_Gb_Eb, 1}, {CMP_Gv_Ev, 1}, {CMP_AL_Ib, 0}, {CMP_eAX_Iv, 0}, {PREFIX_SegOverride_DS, 0}, {AAS, 0}},

    // Row 4
    {{INC_eAX, 0}, {INC_eCX, 0}, {INC_eDX, 0}, {INC_eBX, 0}, {INC_eSP, 0}, {INC_eBP, 0}, {INC_eSI, 0}, {INC_eDI, 0},
     {DEC_eAX, 0}, {DEC_eCX, 0}, {DEC_eDX, 0}, {DEC_eBX, 0}, {DEC_eSP, 0}, {DEC_eBP, 0}, {DEC_eSI, 0}, {DEC_eDI, 0}},

    // Row 5
    {{PUSH_eAX, 0}, {PUSH_eCX, 0}, {PUSH_eDX, 0}, {PUSH_eBX, 0}, {PUSH_eSP, 0}, {PUSH_eBP, 0}, {PUSH_eSI, 0}, {PUSH_eDI, 0},
     {POP_eAX, 0}, {POP_eCX, 0}, {POP_eDX, 0}, {POP_eBX, 0}, {POP_eSP, 0}, {POP_eBP, 0}, {POP_eSI, 0}, {POP_eDI, 0}},

    // Row 6
    {{PUSHA, 0}, {POPA, 0}, {BOUND_Gv_Ma, 1}, {ARPL_Ew_Rw, 1}, {PREFIX_SegOverride_FS, 0}, {PREFIX_SegOverride_GS, 0}, {PREFIX_Operand_Size, 0}, {PREFIX_Address_Size, 0},
     {PUSH_Iv, 0}, {IMUL_GvEvIv, 1}, {PUSH_Ib, 0}, {IMUL_GvEvIb, 1}, {INSB_Yb_DX, 0}, {INSW__D_Yv_DX, 0}, {OUTSB_DX_Xb, 0}, {OUTSW__D_DX_Xv, 0}},

    // Row 7
    {{JCC_JO, 0}, {JCC_JNO, 0}, {JCC_JB, 0}, {JCC_JNB, 0}, {JCC_JZ, 0}, {JCC_JNZ, 0}, {JCC_JBE, 0}, {JCC_JNBE, 0},
     {JCC_JS, 0}, {JCC_JNS, 0}, {JCC_JP, 0}, {JCC_JNP, 0}, {JCC_JL, 0}, {JCC_JNL, 0}, {JCC_JLE, 0}, {JCC_JNLE, 0}},

    // Row 8
    {{IMM_Grp1_Eb_Ib, 1}, {IMM_Grp1_Ev_Iv, 1}, {MOVB_AL_imm8, 0}, {Grp1_Ev_Ib, 1}, {TEST_Eb_Gb, 1}, {TEST_Ev_Gv, 1}, {XCHG_Eb_Gb, 1}, {XCHG_Ev_Gv, 1},
     {MOV_Eb_Gb, 1}, {MOV_Ev_Gv, 1}, {MOV_Gb_Eb, 1}, {MOV_Gv_Ev, 1}, {MOV_Ew_Sw, 1}, {LEA_Gv_M, 1}, {MOV_Sw_Ew, 1}, {POP_Ev, 1}},

    // Row 9
    {{NOP, 0}, {XCHG_eAX_eCX, 0}, {XCHG_eAX_eDX, 0}, {XCHG_eAX_eBX, 0}, {XCHG_eAX_eSP, 0}, {XCHG_eAX_eBP, 0}, {XCHG_eAX_eSI, 0}, {XCHG_eAX_eDI, 0},
     {CBW, 0}, {CWD, 0}, {CALL_Ap, 0}, {WAIT, 0}, {PUSHF_Fv, 0}, {POPF_Fv, 0}, {SAHF, 0}, {LAHF, 0}},

    // Row A
    {{MOV_AL_Ob, 0}, {MOV_eAX_Ov, 0}, {MOV_Ob_AL, 0}, {MOV_Ov_eAX, 0}, {MOVSB_Xb_Yb, 0}, {MOVSW__D_Xv_Yv, 0}, {CMPSB_Xb_Yb, 0}, {CMPSW__D_Xv_Yv, 0},
     {TEST_AL_Ib, 0}, {TEST_eAX_Iv, 0}, {STOSB_Yb_AL, 0}, {STOSW__D_Yv_eAX, 0}, {LODSB_AL_Xb, 0}, {LODSW__D_eAX_Xv, 0}, {SCASB_AL_Xb, 0}, {SCASW__D_eAX_Xv, 0}},

    // Row B
    {{MOV_AL_imm8, 0}, {MOV_CL_imm8, 0}, {MOV_DL_imm8, 0}, {MOV_BL_imm8, 0}, {MOV_AH_imm8, 0}, {MOV_CH_imm8, 0}, {MOV_DH_imm8, 0}, {MOV_BH_imm8, 0},
     {MOV_eAX_Iv, 0}, {MOV_eCX_Iv, 0}, {MOV_eDX_Iv, 0}, {MOV_eBX_Iv, 0}, {MOV_eSP_Iv, 0}, {MOV_eBP_Iv, 0}, {MOV_eSI_Iv, 0}, {MOV_eDI_Iv, 0}},

    // ROW C
    {{Shift_Grp2_Eb_Ib, 1}, {Shift_Grp2_Ev_Ib, 1}, {RET_near_Iw, 0}, {RET_near, 0}, {LES_Gv_Mp, 1}, {LDS_Gv_Mp, 1}, {MOV_Eb_Ib, 1}, {MOV_Ev_Iv, 1},
     {ENTER_Iw_Ib, 0}, {LEAVE, 0}, {RET_far_Iw, 0}, {RET_far, 0}, {INT_3, 0}, {INT_Ib, 0}, {INTO, 0}, {IRET, 0}},

    // Row D
    {{Shift_Grp2_Eb_1, 1}, {Shift_Grp2_Ev_1, 1}, {Shift_Grp2_Eb_CL, 1}, {Shift_Grp2_Ev_CL, 1}, {AAM, 0}, {AAD, 0}, {InvalidOp, 0}, {XLAT, 0},
     {ESC_To_Coprocessor, 1}, {ESC_To_Coprocessor, 1}, {ESC_To_Coprocessor, 1}, {ESC_To_Coprocessor, 1}, {ESC_To_Coprocessor, 1}, {ESC_To_Coprocessor, 1}, {ESC_To_Coprocessor, 1}, {ESC_To_Coprocessor, 1}},

    // ROW E
    {{LOOPNE_Jb, 0}, {LOOPE_Jb, 0}, {LOOP_Jb, 0}, {JCXZ_Jb, 0}, {IN_AL_Ib, 0}, {IN_eAX_Ib, 0}, {OUT_Ib_AL, 0}, {OUT_Ib_eAX, 0},
     {CALL_Jv, 0}, {JMP_Jv, 0}, {JMP_AP, 0}, {JMP_Jb, 0}, {IN_AL_DX, 0}, {IN_eAX_DX, 0}, {OUT_DX_AL, 0}, {OUT_DX_eAX, 0}},

    // Row F
    {{LOCK, 0}, {InvalidOp, 0}, {REPNE, 0}, {REP_REPE, 0}, {HLT, 0}, {CMC, 0}, {Unary_Grp3_Eb, 1}, {Unary_Grp3_Ev, 1},
     {CLC, 0}, {STC, 0}, {CLI, 0}, {STI, 0}, {CLD, 0}, {STD, 0}, {INC__DEC_Grp4, 1}, {INC__DEC_Grp5, 1}}
};

#define ESCAPE_2_byte_opcode_table 0
// int one_byte_opcodemap[16][16] = {
//     // Row 0
//     {ADD_Eb_Gb, ADD_Ev_Gv, ADD_Gb_Eb, ADD_Gv_Ev, ADD_AL_Ib, ADD_eAX_Iv, PUSH_ES,
//      POP_ES, OR_Eb_Gb, OR_Ev_Gv, OR_Gb_Eb, OR_Gv_Ev, OR_AL_Ib, OR_eAX_Iv,
//      PUSH_CS, ESCAPE_2_byte_opcode_table},
//
//     // Row 1
//     {ADC_Eb_Gb, ADC_Ev_Gv, ADC_Gb_Eb, ADC_Gv_Ev, ADC_AL_Ib, ADC_eAX_Iv, PUSH_SS,
//      POP_SS, SBB_Eb_Gb, SBB_Ev_Gv, SBB_Gb_Eb, SBB_Gv_Ev, SBB_AL_Ib, SBB_eAX_Iv,
//      PUSH_DS, POP_DS},
//
//     // Row 2
//     {AND_Eb_Gb, AND_Ev_Gv, AND_Gb_Eb, AND_Gv_Ev, AND_AL_Ib, AND_eAX_Iv,
//      PREFIX_SegOverride_ES, DAA, SUB_Eb_Gb, SUB_Ev_Gv, SUB_Gb_Eb, SUB_Gv_Ev,
//      SUB_AL_Ib, SUB_eAX_Iv, PREFIX_SegOverride_CS, DAS},
//
//     // Row 3
//     {XOR_Eb_Gb, XOR_Ev_Gv, XOR_Gb_Eb, XOR_Gv_Ev, XOR_AL_Ib, XOR_eAX_Iv,
//      PREFIX_SegOverride_SS, AAA, CMP_Eb_Gb, CMP_Ev_Gv, CMP_Gb_Eb, CMP_Gv_Ev,
//      CMP_AL_Ib, CMP_eAX_Iv, PREFIX_SegOverride_DS, AAS},
//
//     // Row 4
//     {INC_eAX, INC_eCX, INC_eDX, INC_eBX, INC_eSP, INC_eBP, INC_eSI, INC_eDI,
//      DEC_eAX, DEC_eCX, DEC_eDX, DEC_eBX, DEC_eSP, DEC_eBP, DEC_eSI, DEC_eDI},
//
//     // Row 5
//     {PUSH_eAX, PUSH_eCX, PUSH_eDX, PUSH_eBX, PUSH_eSP, PUSH_eBP, PUSH_eSI,
//      PUSH_eDI, POP_eAX, POP_eCX, POP_eDX, POP_eBX, POP_eSP, POP_eBP, POP_eSI,
//      POP_eDI},
//
//     // Row 6
//     {PUSHA, POPA, BOUND_Gv_Ma, ARPL_Ew_Rw, PREFIX_SegOverride_FS,
//      PREFIX_SegOverride_GS, PREFIX_Operand_Size, PREFIX_Address_Size, PUSH_Iv,
//      IMUL_GvEvIv, PUSH_Ib, IMUL_GvEvIb, INSB_Yb_DX, INSW__D_Yv_DX, OUTSB_DX_Xb,
//      OUTSW__D_DX_Xv},
//
//     // Row 7
//     {JCC_JO, JCC_JNO, JCC_JB, JCC_JNB, JCC_JZ, JCC_JNZ, JCC_JBE, JCC_JNBE,
//      JCC_JS, JCC_JNS, JCC_JP, JCC_JNP, JCC_JL, JCC_JNL, JCC_JLE, JCC_JNLE},
//
//     // Row 8
//     {IMM_Grp1_Eb_Ib, IMM_Grp1_Ev_Iv, MOVB_AL_imm8, Grp1_Ev_Ib, TEST_Eb_Gb,
//      TEST_Ev_Gv, XCHG_Eb_Gb, XCHG_Ev_Gv, MOV_Eb_Gb, MOV_Ev_Gv, MOV_Gb_Eb,
//      MOV_Gv_Ev, MOV_Ew_Sw, LEA_Gv_M, MOV_Sw_Ew, POP_Ev},
//
//     // Row 9
//     {NOP, XCHG_eAX_eCX, XCHG_eAX_eDX, XCHG_eAX_eBX, XCHG_eAX_eSP, XCHG_eAX_eBP,
//      XCHG_eAX_eSI, XCHG_eAX_eDI, CBW, CWD, CALL_Ap, WAIT, PUSHF_Fv, POPF_Fv,
//      SAHF, LAHF},
//
//     // Row A
//     {MOV_AL_Ob, MOV_eAX_Ov, MOV_Ob_AL, MOV_Ov_eAX, MOVSB_Xb_Yb, MOVSW__D_Xv_Yv,
//      CMPSB_Xb_Yb, CMPSW__D_Xv_Yv, TEST_AL_Ib, TEST_eAX_Iv, STOSB_Yb_AL,
//      STOSW__D_Yv_eAX, LODSB_AL_Xb, LODSW__D_eAX_Xv, SCASB_AL_Xb,
//      SCASW__D_eAX_Xv},
//
//     // Row B
//     {MOV_AL_imm8, MOV_CL_imm8, MOV_DL_imm8, MOV_BL_imm8, MOV_AH_imm8,
//      MOV_CH_imm8, MOV_DH_imm8, MOV_BH_imm8, MOV_eAX_Iv, MOV_eCX_Iv, MOV_eDX_Iv, MOV_eBX_Iv,
//      MOV_eSP_Iv, MOV_eBP_Iv, MOV_eSI_Iv, MOV_eDI_Iv},
//
//     // ROW C
//     {Shift_Grp2_Eb_Ib, Shift_Grp2_Ev_Ib, RET_near_Iw, RET_near, LES_Gv_Mp,
//      LDS_Gv_Mp, MOV_Eb_Ib, MOV_Ev_Iv, ENTER_Iw_Ib, LEAVE, RET_far_Iw, RET_far,
//      INT_3, INT_Ib, INTO, IRET},
//
//     // Row D
//     {
//         Shift_Grp2_Eb_1,
//         Shift_Grp2_Ev_1,
//         Shift_Grp2_Eb_CL,
//         Shift_Grp2_Ev_CL,
//         AAM,
//         AAD,
//         InvalidOp,
//         XLAT,
//         ESC_To_Coprocessor,
//         ESC_To_Coprocessor,
//         ESC_To_Coprocessor,
//         ESC_To_Coprocessor,
//         ESC_To_Coprocessor,
//         ESC_To_Coprocessor,
//         ESC_To_Coprocessor,
//         ESC_To_Coprocessor,
//     },
//
//     // ROW E
//     {
//         LOOPNE_Jb,
//         LOOPE_Jb,
//         LOOP_Jb,
//         JCXZ_Jb,
//         IN_AL_Ib,
//         IN_eAX_Ib,
//         OUT_Ib_AL,
//         OUT_Ib_eAX,
//         CALL_Jv,
//         JMP_Jv,
//         JMP_AP,
//         JMP_Jb,
//         IN_AL_DX,
//         IN_eAX_DX,
//         OUT_DX_AL,
//         OUT_DX_eAX,
//     },
//
//     // Row F
//     {
//         LOCK,
//         InvalidOp,
//         REPNE,
//         REP_REPE,
//         HLT,
//         CMC,
//         Unary_Grp3_Eb,
//         Unary_Grp3_Ev,
//         CLC,
//         STC,
//         CLI,
//         STI,
//         CLD,
//         STD,
//         INC__DEC_Grp4,
//         INC__DEC_Grp5,
//     }};

/**
 * @brief Lookup table for two-byte x86 opcodes (prefixed with 0x0F).
 *
 * This 16x16 array is used for opcodes that begin with the 0x0F prefix.
 * The row and column indices map to the second byte of the opcode, similar to
 * the one_byte_opcodemap.
 *
 * Entries marked 'InvalidOp' indicate unused or reserved opcode combinations.
 */
int two_byte_opcodemap[16][16] = {
    // Row 0
    {Grp6, Grp7, LAR_Gv_Ew, LSL_Gv_Ew, InvalidOp, InvalidOp, CLTS, InvalidOp,
     INVD, WBINVD, InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp,
     InvalidOp},

    // Row 1
    {InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp,
     InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp,
     InvalidOp, InvalidOp, InvalidOp, InvalidOp},

    // Row 2
    {MOV_Cd_Rd, MOV_Dd_Rd, MOV_Rd_Cd, MOV_Rd_Dd, MOV_Td_Rd, InvalidOp,
     MOV_Rd_Td, InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp,
     InvalidOp, InvalidOp, InvalidOp, InvalidOp},

    // Row 3
    {InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp,
     InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp,
     InvalidOp, InvalidOp, InvalidOp, InvalidOp},

    // Row 4
    {InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp,
     InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp,
     InvalidOp, InvalidOp, InvalidOp, InvalidOp},

    // Row 5
    {InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp,
     InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp,
     InvalidOp, InvalidOp, InvalidOp, InvalidOp},

    // Row 6
    {InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp,
     InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp,
     InvalidOp, InvalidOp, InvalidOp, InvalidOp},

    // Row 7
    {InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp,
     InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp,
     InvalidOp, InvalidOp, InvalidOp, InvalidOp},

    // Row 8
    {JV_JO, JV_JNO, JV_JB, JV_JNB, JV_JZ, JV_JNZ, JV_JBE, JV_JNBE, JV_JS,
     JV_JNS, JV_JP, JV_JNP, JV_JL, JV_JNL, JV_JLE, JV_JNLE},

    // Row 9
    {Eb_SETO, Eb_SETNO, Eb_SETB, Eb_SETNB, Eb_SETZ, Eb_SETNZ, Eb_SETBE,
     Eb_SETNBE, Eb_SETS, Eb_SETNS, Eb_SETP, Eb_SETNP, Eb_SETL, Eb_SETNL,
     Eb_SETLE, Eb_SETNLE},

    // Row A
    {PUSH_FS, POP_FS, InvalidOp, BT_Ev_Gv, SHLD_EvGvIb, SHLD_EvGvCL,
     CMPXCHG_Eb_Gb, CMPXCHG_Ev_Gv, PUSH_GS, POP_GS, InvalidOp, BTS_Ev_Gv,
     SHRD_EvGvIb, SHRD_EvGvCL, InvalidOp, IMUL_Gv_Ev},

    // Row B
    {InvalidOp, InvalidOp, LSS_Mp, BTR_Ev_Gv, LFS_Mp, LGS_Mp, MOVZX_Gv_Eb,
     MOVZX_Gv_Ew, InvalidOp, InvalidOp, Grp8_Ev_Ib, BTC_Ev_Gv, BSF_Gv_Ev,
     BSR_Gv_Ev, MOVSX_Gv_Eb, MOVSX_Gv_Ew},

    // Row C
    {XADD_Eb_Gb, XADD_Ev_Gv, InvalidOp, InvalidOp, InvalidOp, InvalidOp,
     InvalidOp, InvalidOp, BSWAP_EAX, BSWAP_ECX, BSWAP_EDX, BSWAP_EBX,
     BSWAP_ESP, BSWAP_EBP, BSWAP_ESI, BSWAP_EDI},

    // Row D
    {InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp,
     InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp,
     InvalidOp, InvalidOp, InvalidOp, InvalidOp},

    // Row E
    {InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp,
     InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp,
     InvalidOp, InvalidOp, InvalidOp, InvalidOp},

    // Row F
    {InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp,
     InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp, InvalidOp,
     InvalidOp, InvalidOp, InvalidOp, InvalidOp},
};

/**
 * @brief Lookup table for x86 grouped opcodes.
 *
 * This 8x8 array is used for instructions that are part of an opcode "group".
 * These instructions share a common primary opcode byte, and their specific
 * operation is further determined by the 'reg' field (bits 5-3) of the ModR/M
 * byte.
 *
 * The first dimension (0-7) corresponds to the group number, and the second
 * dimension (0-7) corresponds to the value of the 'reg' field within the ModR/M
 * byte. For example, Grp1 (index 0) uses ModR/M to select ADD, OR, ADC, etc.
 * Entries marked 'InvalidOp' indicate unused or reserved combinations within a
 * group.
 */
int group_opcodemap[8][8] = {
    // Grp 1
    {
        Grp1_ADD,
        Grp1_OR,
        Grp1_ADC,
        Grp1_SBB,
        Grp1_AND,
        Grp1_SUB,
        Grp1_XOR,
        Grp1_CMP,
    },

    // Grp 2
    {
        Grp2_ROL,
        Grp2_ROR,
        Grp2_RCL,
        Grp2_RCR,
        Grp2_SHL,
        Grp2_SHR,
        Grp2_SHL,
        Grp2_SAR,
    },

    // Grp 3
    {Grp3_TEST_Ib__Iv, UNDEFINED, Grp3_NOT, Grp3_NEG, Grp3_MUL_AL__eAX,
     Grp3_IMUL_AL__eAX, Grp3_DIV_AL__eAX, Grp3_IDIV_AL__eAX},

    // Grp 4
    {
        Grp4_INC_Eb,
        Grp4_DEC_Eb,
        InvalidOp,
        InvalidOp,
        InvalidOp,
        InvalidOp,
        InvalidOp,
        InvalidOp,
    },

    // Grp 5
    {
        Grp5_INC_Ev,
        Grp5_IDEC_Ev,
        Grp5_CALL_Ev,
        Grp5_CALL_eP,
        Grp5_JMP_Ev,
        Grp5_JMP_Ep,
        Grp5_PUSH_Ev,
        InvalidOp,
    },

    // Grp 6
    {Grp6_SLDT_Ew, Grp6_STR_Ew, Grp6_LLDT_Ew, Grp6_LTR_Ew, Grp6_VERR_Ew,
     Grp6_VERW_Ew, InvalidOp, InvalidOp},

    // Grp 7
    {
        Grp7_SGDT_Ms,
        Grp7_SIDT_Ms,
        Grp7_LGDT_Ms,
        Grp7_LIDT_Ms,
        Grp7_SMSW_Ew,
        InvalidOp,
        Grp7_LMSW_Ew,
        InvalidOp,
    },

    // Grp 8
    {InvalidOp, InvalidOp, InvalidOp, InvalidOp, Grp8_BT, Grp8_BTS, Grp8_BTR,
     Grp8_BTC},
};
