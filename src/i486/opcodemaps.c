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
 * This 16x16 array maps the first byte of an opcode to its corresponding instruction.
 * The row index represents the most significant nibble (bits 7-4) of the opcode byte,
 * and the column index represents the least significant nibble (bits 3-0).
 *
 * Each entry is a symbolic constant (e.g., ADD_Eb_Gb) representing a specific x86 instruction.
 * The order of these opcodes is critical for correct decoding.
 */
int one_byte_opcodemap[16][16] = {
    // Row 0
    {ADD_Eb_Gb, ADD_Ev_Gv, ADD_Gb_Eb, ADD_Gv_Ev, ADD_AL_Ib, ADD_eAX_Iv, PUSH_ES,
     POP_ES, OR_Eb_Gb, OR_Ev_Gv, OR_Gb_Eb, OR_Gv_Ev, OR_AL_Ib, OR_eAX_Iv,
     PUSH_CS, ESCAPE_2_byte},

    // Row 1
    {ADC_Eb_Gb, ADC_Ev_Gv, ADC_Gb_Eb, ADC_Gv_Ev, ADC_AL_Ib, ADC_eAX_Iv, PUSH_SS,
     POP_SS, SBB_Eb_Gb, SBB_Ev_Gv, SBB_Gb_Eb, SBB_Gv_Ev, SBB_AL_Ib, SBB_eAX_Iv,
     PUSH_DS, POP_DS},

    // Row 2
    {AND_Eb_Gb, AND_Ev_Gv, AND_Gb_Eb, AND_Gv_Ev, AND_AL_Ib, AND_eAX_Iv,
     PREFIX_SegOverride_ES, DAA, SUB_Eb_Gb, SUB_Ev_Gv, SUB_Gb_Eb, SUB_Gv_Ev,
     SUB_AL_Ib, SUB_eAX_Iv, PREFIX_SegOverride_CS, DAS},

    // Row 3
    {XOR_Eb_Gb, XOR_Ev_Gv, XOR_Gb_Eb, XOR_Gb_Ev, XOR_AL_Ib, XOR_eAX_Iv,
     PREFIX_SegOverride_SS, AAA, CMP_Eb_Gb, CMP_Ev_Gv, CMP_Gb_Eb, CMP_Gv_Ev,
     CMP_AL_Ib, CMP_eAX_Iv, PREFIX_SegOverride_DS, AAS},

    // Row 4
    {INC_eAX, INC_eCX, INC_eDX, INC_eBX, INC_eSP, INC_eBP, INC_eSI, INC_eDI,
     DEC_eAX, DEC_eCX, DEC_eDX, DEC_eBX, DEC_eSP, DEC_eBP, DEC_eSI, DEC_eDI},

    // Row 5
    {PUSH_eAX, PUSH_eCX, PUSH_eDX, PUSH_eBX, PUSH_eSP, PUSH_eBP, PUSH_eSI,
     PUSH_eDI, POP_eAX, POP_eCX, POP_eDX, POP_eBX, POP_eSP, POP_eBP, POP_eSI,
     POP_eDI},

    // Row 6
    {PUSHA, POPA, BOUND_Gv_Ma, ARPL_Ew_Rw, PREFIX_SegOverride_FS,
     PREFIX_SegOverride_GS, PREFIX_Operand_Size, PREFIX_Address_Size, PUSH_Iv,
     IMUL_GvEvIv, PUSH_Ib, IMUL_GvEvIb, INSB_Yb_DX, INSW__D_Yv_DX, OUTSB_DX_Xb,
     OUTSW__D_DX_Xv},

    // Row 7
    {JCC_JO, JCC_JNO, JCC_JB, JCC_JNB, JCC_JZ, JCC_JNZ, JCC_JBE, JCC_JNBE,
     JCC_JS, JCC_JNS, JCC_JP, JCC_JNP, JCC_JL, JCC_JNL, JCC_JLE, JCC_JNLE},

    // Row 8
    {IMM_Grpl_Eb_Ib, IMM_Grpl_Ev_Iv, MOVB_AL_imm8, Grpl_Ev_Ib, TEST_Eb_Gb,
     TEST_Ev_Gv, XCHG_Eb_Gb, XCHG_Ev_Gv, MOV_Eb_Gb, MOV_Ev_Gv, MOV_Gb_Eb,
     MOV_Gv_Ev, MOV_Ew_Sw, LEA_Gv_M, MOV_Sw_Ew, POP_Ev},

    // Row 9
    {NOP, XCHG_eAX_eCX, XCHG_eAX_eDX, XCHG_eAX_eBX, XCHG_eAX_eSP, XCHG_eAX_eBP,
     XCHG_eAX_eSI, XCHG_eAX_eDI, CBW, CWD, CALL_Ap, WAIT, PUSHF_Fv, POPF_Fv,
     SAHF, LAHF},

    // Row A
    {MOV_AL_Ob, MOV_eAX_Ov, MOV_Ob_AL, MOV_Ov_eAX, MOVSB_Xb_Yb, MOVSW__D_Xv_Yv,
     CMPSB_Xb_Yb, CMPSW__D_Xv_Yv, TEST_AL_Ib, TEST_eAX_Iv, STOSB_Yb_AL,
     STOSW__D_Yv_eAX, LODSB_AL_Xb, LODSW__D_eAX_Xv, SCASB_AL_Xb,
     SCASW__D_eAX_Xv},

    // Row B
    {MOV_AL, MOV_CL, MOV_DL, MOV_BL, MOV_AH, MOV_CH, MOV_DH, MOV_BH, MOV_eAX,
     MOV_eCX, MOV_eDX, MOV_eBX, MOV_eSP, MOV_eBP, MOV_eSI, MOV_eDI},

    // ROW C
    {Shift_Grp2_Eb_Ib, Shift_Grp2_Ev_Ib, RET_near_Iw, InvalidOp, LES_Gv_Mp,
     LDS_Gv_Mp, MOV_Eb_Ib, MOV_Ev_Iv, ENTER_Iw_Ib, LEAVE, RET_far_Iw, InvalidOp,
     INT_3, INT_Ib, INTO, IRET},

    // Row D
    {
        Shift_Grp2_Eb_1,
        Shift_Grp2_Ev_1,
        Shift_Grp2_Eb_CL,
        Shift_Grp2_Ev_CL,
        AAM,
        AAD,
        InvalidOp,
        XLAT,
        ESC_To_Coprocessor,
        ESC_To_Coprocessor,
        ESC_To_Coprocessor,
        ESC_To_Coprocessor,
        ESC_To_Coprocessor,
        ESC_To_Coprocessor,
        ESC_To_Coprocessor,
        ESC_To_Coprocessor,
    },

    // ROW E
    {
        LOOPNE_Jb,
        LOOPE_Jb,
        LOOP_Jb,
        JCXZ_Jb,
        IN_AL_Ib,
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
    },

    // Row F
    {
        LOCK,
        InvalidOp,
        REPNE,
        REP_REPE,
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
    }};

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
 * operation is further determined by the 'reg' field (bits 5-3) of the ModR/M byte.
 *
 * The first dimension (0-7) corresponds to the group number, and the second dimension (0-7)
 * corresponds to the value of the 'reg' field within the ModR/M byte.
 * For example, Grp1 (index 0) uses ModR/M to select ADD, OR, ADC, etc.
 * Entries marked 'InvalidOp' indicate unused or reserved combinations within a group.
 */
int group_opcodemap[8][8] = {
  // Grp 1
    {
        Grp_ADD,
        Grp_OR,
        Grp_ADC,
        Grp_SBB,
        Grp_AND,
        Grp_SUB,
        Grp_XOR,
        Grp_CMP,
    },

    // Grp 2
    {
        Grp_ROL,
        Grp_ROR,
        Grp_RCL,
        Grp_RCR,
        Grp_SHL,
        Grp_SHR,
        Grp_SHL,
        Grp_SAR,
    },

    // Grp 3
    {Grp_TEST_Ib__Iv, Grp_TEST_Ib__Iv, Grp_NOT, Grp_NEG, Grp_MUL_AL__eAX,
     Grp_IMUL_AL__eAX, Grp_DIV_AL__eAX, Grp_IDIV_AL__eAX},

    // Grp 4
    {
        Grp_INC_Eb,
        Grp_DEC_Eb,
        InvalidOp,
        InvalidOp,
        InvalidOp,
        InvalidOp,
        InvalidOp,
        InvalidOp,
    },

    // Grp 5
    {
        Grp_INC_Ev,
        Grp_IDEC_Ev,
        Grp_CALL_Ev,
        Grp_CALL_eP,
        Grp_JMP_Ev,
        Grp_JMP_Ep,
        Grp_PUSH_Ev,
        InvalidOp,
    },

    // Grp 6
    {Grp_SLDT_Ew, Grp_STR_Ew, Grp_LLDT_Ew, Grp_LTR_Ew, Grp_VERR_Ew, Grp_VERW_Ew,
     InvalidOp, InvalidOp},

    // Grp 7
    {
        Grp_SGDT_Ms,
        Grp_SIDT_Ms,
        Grp_LGDT_Ms,
        Grp_LIDT_Ms,
        Grp_SMSW_Ew,
        InvalidOp,
        Grp_LMSW_Ew,
        InvalidOp,
    },

    // Grp 8
    {InvalidOp, InvalidOp, InvalidOp, InvalidOp, Grp_BT, Grp_BTS, Grp_BTR,
     Grp_BTC},
};
