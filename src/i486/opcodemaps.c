/**
 * @file
 * @brief Defines x86 opcode maps for one-byte, two-byte, and grouped opcodes.
 *
 * These maps are essential for the i486 instruction decoder,
 * providing a structured lookup for instruction decoding based on opcode bytes.
 */
#include <acme/i486/decoder.h>

/**
 * @brief Primary Lookup Table for 80486 One-Byte Opcodes.
 *
 * This 16x16 array provides the initial decoding stage for x86 instructions.
 * The table maps the opcode byte to a structural pair consisting of the
 * Instruction ID and a ModR/M fetch flag.
 *
 * @structure
 * Each entry is an OpcodeEntry containing:
 *  - opcode: A symbolic constant (e.g., ADD_Eb_Gb) identifying the instruction.
 *  - has_modrm: A boolean-style flag (1 or 0). If 1, the decoder must fetch
 *    the subsequent ModR/M byte to resolve operands or opcode extensions.
 *
 * @organization
 * - Row Index: Most Significant Nibble (bits 7-4) of the opcode.
 * - Column Index: Least Significant Nibble (bits 3-0) of the opcode.
 *
 * @design_note
 * This table implements a "Separation of Concerns" architecture. It identifies
 * the instruction but delegates operand resolution, SIB-byte processing, and
 * displacement fetching to downstream functions based on the 'has_modrm' state.
 */

#define ESCAPE_2_byte_opcode_table 0
OpcodeEntry one_byte_opcodemap[16][16] = {
    // Row 0
    {{ADD_Eb_Gb, 1},
     {ADD_Ev_Gv, 1},
     {ADD_Gb_Eb, 1},
     {ADD_Gv_Ev, 1},
     {ADD_AL_Ib, 0},
     {ADD_eAX_Iv, 0},
     {PUSH_ES, 0},
     {POP_ES, 0},
     {OR_Eb_Gb, 1},
     {OR_Ev_Gv, 1},
     {OR_Gb_Eb, 1},
     {OR_Gv_Ev, 1},
     {OR_AL_Ib, 0},
     {OR_eAX_Iv, 0},
     {PUSH_CS, 0},
     {ESCAPE_2_byte_opcode_table, 0}},

    // Row 1
    {{ADC_Eb_Gb, 1},
     {ADC_Ev_Gv, 1},
     {ADC_Gb_Eb, 1},
     {ADC_Gv_Ev, 1},
     {ADC_AL_Ib, 0},
     {ADC_eAX_Iv, 0},
     {PUSH_SS, 0},
     {POP_SS, 0},
     {SBB_Eb_Gb, 1},
     {SBB_Ev_Gv, 1},
     {SBB_Gb_Eb, 1},
     {SBB_Gv_Ev, 1},
     {SBB_AL_Ib, 0},
     {SBB_eAX_Iv, 0},
     {PUSH_DS, 0},
     {POP_DS, 0}},

    // Row 2
    {{AND_Eb_Gb, 1},
     {AND_Ev_Gv, 1},
     {AND_Gb_Eb, 1},
     {AND_Gv_Ev, 1},
     {AND_AL_Ib, 0},
     {AND_eAX_Iv, 0},
     {PREFIX_SegOverride_ES, 0},
     {DAA, 0},
     {SUB_Eb_Gb, 1},
     {SUB_Ev_Gv, 1},
     {SUB_Gb_Eb, 1},
     {SUB_Gv_Ev, 1},
     {SUB_AL_Ib, 0},
     {SUB_eAX_Iv, 0},
     {PREFIX_SegOverride_CS, 0},
     {DAS, 0}},

    // Row 3
    {{XOR_Eb_Gb, 1},
     {XOR_Ev_Gv, 1},
     {XOR_Gb_Eb, 1},
     {XOR_Gv_Ev, 1},
     {XOR_AL_Ib, 0},
     {XOR_eAX_Iv, 0},
     {PREFIX_SegOverride_SS, 0},
     {AAA, 0},
     {CMP_Eb_Gb, 1},
     {CMP_Ev_Gv, 1},
     {CMP_Gb_Eb, 1},
     {CMP_Gv_Ev, 1},
     {CMP_AL_Ib, 0},
     {CMP_eAX_Iv, 0},
     {PREFIX_SegOverride_DS, 0},
     {AAS, 0}},

    // Row 4
    {{INC_eAX, 0},
     {INC_eCX, 0},
     {INC_eDX, 0},
     {INC_eBX, 0},
     {INC_eSP, 0},
     {INC_eBP, 0},
     {INC_eSI, 0},
     {INC_eDI, 0},
     {DEC_eAX, 0},
     {DEC_eCX, 0},
     {DEC_eDX, 0},
     {DEC_eBX, 0},
     {DEC_eSP, 0},
     {DEC_eBP, 0},
     {DEC_eSI, 0},
     {DEC_eDI, 0}},

    // Row 5
    {{PUSH_eAX, 0},
     {PUSH_eCX, 0},
     {PUSH_eDX, 0},
     {PUSH_eBX, 0},
     {PUSH_eSP, 0},
     {PUSH_eBP, 0},
     {PUSH_eSI, 0},
     {PUSH_eDI, 0},
     {POP_eAX, 0},
     {POP_eCX, 0},
     {POP_eDX, 0},
     {POP_eBX, 0},
     {POP_eSP, 0},
     {POP_eBP, 0},
     {POP_eSI, 0},
     {POP_eDI, 0}},

    // Row 6
    {{PUSHA, 0},
     {POPA, 0},
     {BOUND_Gv_Ma, 1},
     {ARPL_Ew_Rw, 1},
     {PREFIX_SegOverride_FS, 0},
     {PREFIX_SegOverride_GS, 0},
     {PREFIX_Operand_Size, 0},
     {PREFIX_Address_Size, 0},
     {PUSH_Iv, 0},
     {IMUL_GvEvIv, 1},
     {PUSH_Ib, 0},
     {IMUL_GvEvIb, 1},
     {INSB_Yb_DX, 0},
     {INSW__D_Yv_DX, 0},
     {OUTSB_DX_Xb, 0},
     {OUTSW__D_DX_Xv, 0}},

    // Row 7
    {{JCC_JO, 0},
     {JCC_JNO, 0},
     {JCC_JB, 0},
     {JCC_JNB, 0},
     {JCC_JZ, 0},
     {JCC_JNZ, 0},
     {JCC_JBE, 0},
     {JCC_JNBE, 0},
     {JCC_JS, 0},
     {JCC_JNS, 0},
     {JCC_JP, 0},
     {JCC_JNP, 0},
     {JCC_JL, 0},
     {JCC_JNL, 0},
     {JCC_JLE, 0},
     {JCC_JNLE, 0}},

    // Row 8
    {{IMM_Grp1_Eb_Ib, 1},
     {IMM_Grp1_Ev_Iv, 1},
     {MOVB_AL_imm8, 0},
     {Grp1_Ev_Ib, 1},
     {TEST_Eb_Gb, 1},
     {TEST_Ev_Gv, 1},
     {XCHG_Eb_Gb, 1},
     {XCHG_Ev_Gv, 1},
     {MOV_Eb_Gb, 1},
     {MOV_Ev_Gv, 1},
     {MOV_Gb_Eb, 1},
     {MOV_Gv_Ev, 1},
     {MOV_Ew_Sw, 1},
     {LEA_Gv_M, 1},
     {MOV_Sw_Ew, 1},
     {POP_Ev, 1}},

    // Row 9
    {{NOP, 0},
     {XCHG_eAX_eCX, 0},
     {XCHG_eAX_eDX, 0},
     {XCHG_eAX_eBX, 0},
     {XCHG_eAX_eSP, 0},
     {XCHG_eAX_eBP, 0},
     {XCHG_eAX_eSI, 0},
     {XCHG_eAX_eDI, 0},
     {CBW, 0},
     {CWD, 0},
     {CALL_Ap, 0},
     {WAIT, 0},
     {PUSHF_Fv, 0},
     {POPF_Fv, 0},
     {SAHF, 0},
     {LAHF, 0}},

    // Row A
    {{MOV_AL_Ob, 0},
     {MOV_eAX_Ov, 0},
     {MOV_Ob_AL, 0},
     {MOV_Ov_eAX, 0},
     {MOVSB_Xb_Yb, 0},
     {MOVSW__D_Xv_Yv, 0},
     {CMPSB_Xb_Yb, 0},
     {CMPSW__D_Xv_Yv, 0},
     {TEST_AL_Ib, 0},
     {TEST_eAX_Iv, 0},
     {STOSB_Yb_AL, 0},
     {STOSW__D_Yv_eAX, 0},
     {LODSB_AL_Xb, 0},
     {LODSW__D_eAX_Xv, 0},
     {SCASB_AL_Xb, 0},
     {SCASW__D_eAX_Xv, 0}},

    // Row B
    {{MOV_AL_imm8, 0},
     {MOV_CL_imm8, 0},
     {MOV_DL_imm8, 0},
     {MOV_BL_imm8, 0},
     {MOV_AH_imm8, 0},
     {MOV_CH_imm8, 0},
     {MOV_DH_imm8, 0},
     {MOV_BH_imm8, 0},
     {MOV_eAX_Iv, 0},
     {MOV_eCX_Iv, 0},
     {MOV_eDX_Iv, 0},
     {MOV_eBX_Iv, 0},
     {MOV_eSP_Iv, 0},
     {MOV_eBP_Iv, 0},
     {MOV_eSI_Iv, 0},
     {MOV_eDI_Iv, 0}},

    // ROW C
    {{Shift_Grp2_Eb_Ib, 1},
     {Shift_Grp2_Ev_Ib, 1},
     {RET_near_Iw, 0},
     {RET_near, 0},
     {LES_Gv_Mp, 1},
     {LDS_Gv_Mp, 1},
     {MOV_Eb_Ib, 1},
     {MOV_Ev_Iv, 1},
     {ENTER_Iw_Ib, 0},
     {LEAVE, 0},
     {RET_far_Iw, 0},
     {RET_far, 0},
     {INT_3, 0},
     {INT_Ib, 0},
     {INTO, 0},
     {IRET, 0}},

    // Row D
    {{Shift_Grp2_Eb_1, 1},
     {Shift_Grp2_Ev_1, 1},
     {Shift_Grp2_Eb_CL, 1},
     {Shift_Grp2_Ev_CL, 1},
     {AAM, 0},
     {AAD, 0},
     {InvalidOp, 0},
     {XLAT, 0},
     {ESC_To_Coprocessor, 1},
     {ESC_To_Coprocessor, 1},
     {ESC_To_Coprocessor, 1},
     {ESC_To_Coprocessor, 1},
     {ESC_To_Coprocessor, 1},
     {ESC_To_Coprocessor, 1},
     {ESC_To_Coprocessor, 1},
     {ESC_To_Coprocessor, 1}},

    // ROW E
    {{LOOPNE_Jb, 0},
     {LOOPE_Jb, 0},
     {LOOP_Jb, 0},
     {JCXZ_Jb, 0},
     {IN_AL_Ib, 0},
     {IN_eAX_Ib, 0},
     {OUT_Ib_AL, 0},
     {OUT_Ib_eAX, 0},
     {CALL_Jv, 0},
     {JMP_Jv, 0},
     {JMP_AP, 0},
     {JMP_Jb, 0},
     {IN_AL_DX, 0},
     {IN_eAX_DX, 0},
     {OUT_DX_AL, 0},
     {OUT_DX_eAX, 0}},

    // Row F
    {{LOCK, 0},
     {InvalidOp, 0},
     {REPNE, 0},
     {REP_REPE, 0},
     {HLT, 0},
     {CMC, 0},
     {Unary_Grp3_Eb, 1},
     {Unary_Grp3_Ev, 1},
     {CLC, 0},
     {STC, 0},
     {CLI, 0},
     {STI, 0},
     {CLD, 0},
     {STD, 0},
     {INC__DEC_Grp4, 1},
     {INC__DEC_Grp5, 1}}};

/**
 * @brief Secondary Lookup Table for 80486 Two-Byte (0Fh) Opcodes.
 *
 * This table is indexed by the second byte of an instruction after an 0Fh
 * prefix has been detected.
 */
// TODO: make sure it is correct and check all InvalidOp entries as new instrucions are introduced in late 486 versions
OpcodeEntry two_byte_opcodemap[16][16] = {
    // Row 0
    {{Grp6, 1},
     {Grp7, 1},
     {LAR_Gv_Ew, 1},
     {LSL_Gv_Ew, 1},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {CLTS, 0},
     {InvalidOp, 0},
     {INVD, 0},
     {WBINVD, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0}},

    // Row 1
    {{InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0}},

    // Row 2
    {{MOV_Cd_Rd, 1},
     {MOV_Dd_Rd, 1},
     {MOV_Rd_Cd, 1},
     {MOV_Rd_Dd, 1},
     {MOV_Td_Rd, 1},
     {InvalidOp, 0},
     {MOV_Rd_Td, 1},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0}},

    // Row 3
    {{InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0}},

    // Row 4
    {{InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0}},

    // Row 5
    {{InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0}},

    // Row 6
    {{InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0}},

    // Row 7
    {{InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0}},

    // Row 8
    {{JV_JO, 0},
     {JV_JNO, 0},
     {JV_JB, 0},
     {JV_JNB, 0},
     {JV_JZ, 0},
     {JV_JNZ, 0},
     {JV_JBE, 0},
     {JV_JNBE, 0},
     {JV_JS, 0},
     {JV_JNS, 0},
     {JV_JP, 0},
     {JV_JNP, 0},
     {JV_JL, 0},
     {JV_JNL, 0},
     {JV_JLE, 0},
     {JV_JNLE, 0}},

    // Row 9
    {{Eb_SETO, 1},
     {Eb_SETNO, 1},
     {Eb_SETB, 1},
     {Eb_SETNB, 1},
     {Eb_SETZ, 1},
     {Eb_SETNZ, 1},
     {Eb_SETBE, 1},
     {Eb_SETNBE, 1},
     {Eb_SETS, 1},
     {Eb_SETNS, 1},
     {Eb_SETP, 1},
     {Eb_SETNP, 1},
     {Eb_SETL, 1},
     {Eb_SETNL, 1},
     {Eb_SETLE, 1},
     {Eb_SETNLE, 1}},

    // Row A
    {{PUSH_FS, 0},
     {POP_FS, 0},
     {InvalidOp, 0},
     {BT_Ev_Gv, 1},
     {SHLD_EvGvIb, 1},
     {SHLD_EvGvCL, 1},
     {CMPXCHG_Eb_Gb, 1},
     {CMPXCHG_Ev_Gv, 1},
     {PUSH_GS, 0},
     {POP_GS, 0},
     {InvalidOp, 0},
     {BTS_Ev_Gv, 1},
     {SHRD_EvGvIb, 1},
     {SHRD_EvGvCL, 1},
     {InvalidOp, 0},
     {IMUL_Gv_Ev, 1}},

    // Row B
    {{InvalidOp, 0},
     {InvalidOp, 0},
     {LSS_Mp, 1},
     {BTR_Ev_Gv, 1},
     {LFS_Mp, 1},
     {LGS_Mp, 1},
     {MOVZX_Gv_Eb, 1},
     {MOVZX_Gv_Ew, 1},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {Grp8_Ev_Ib, 1},
     {BTC_Ev_Gv, 1},
     {BSF_Gv_Ev, 1},
     {BSR_Gv_Ev, 1},
     {MOVSX_Gv_Eb, 1},
     {MOVSX_Gv_Ew, 1}},

    // Row C
    {{XADD_Eb_Gb, 1},
     {XADD_Ev_Gv, 1},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {BSWAP_EAX, 0},
     {BSWAP_ECX, 0},
     {BSWAP_EDX, 0},
     {BSWAP_EBX, 0},
     {BSWAP_ESP, 0},
     {BSWAP_EBP, 0},
     {BSWAP_ESI, 0},
     {BSWAP_EDI, 0}},

    // Row D
    {{InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0}},

    // Row E
    {{InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0}},

    // Row F
    {{InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0},
     {InvalidOp, 0}},
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
