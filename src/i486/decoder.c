#include <acme/i486/decoder.h>
#include <assert.h>
#include <stdbool.h>

#define get_mod_reg_field(mod) ((mod >> 3) & 0b111)
#define get_mod_mod_field(mod) ((mod >> 6) & 0b11)
#define get_mod_rm_field(mod) (mod & 0b111)

// convert it to inline function
#define get_addressing_mode(cpu) 0

#define ADRESSING_MODE_16 0
#define ADRESSING_MODE_32 1

// NOTE: temporary fetch

#define FETCH() 0

#define GROUP_1 0
#define GROUP_2 1
#define GROUP_3 2
#define GROUP_4 3
#define GROUP_5 4
#define GROUP_6 5
#define GROUP_7 6
#define GROUP_8 7

static inline void get_opcodemap_row_col(uint8_t opcode_byte, int *row,
                                         int *col) {
  *row = opcode_byte >> 4;
  *col = opcode_byte & 0x0F;
}

static inline void fill_instruction_mod(Instruction *instruction, int inst_name,
                                        int mod_byte) {
  instruction->name = inst_name;
  instruction->mod_field = get_mod_mod_field(mod_byte);
  instruction->reg_field = get_mod_reg_field(mod_byte);
  instruction->rm_field = get_mod_rm_field(mod_byte);
}

// don't fill instructin->name filed
static inline void fill_instruction_mod_only(Instruction *instruction,
                                             int mod_byte) {
  instruction->mod_field = get_mod_mod_field(mod_byte);
  instruction->reg_field = get_mod_reg_field(mod_byte);
  instruction->rm_field = get_mod_rm_field(mod_byte);
}

// TODO : check for opcode map and opcodes and implement opcode table in decoder
// []

extern int one_byte_opcodemap[16][16];

extern int two_byte_opcodemap[16][16];

extern int group_opcodemap[8][8];

// they are globals specific to decoder
static int opcode = 0;
static int opcodemap_row = 0;
static int opcodemap_col = 0;
static int opcode_name = 0;

// TODO: implement decoder no testing required for now it's simple enough
// NOTE: A decoder should be simple as it don't have to calcluate effective
// address or any operands
// it better left to execution unit

AcmeStatus decode(Cpu *cpu, Instruction *instruction) {

  // Temporary variable to hold different mod fields
  uint32_t tmp_reg = 0;
  opcode = FETCH();

  if (opcode == 0x0F) {
    // NOTE: Two byte opcodemap
    opcode = FETCH();
    get_opcodemap_row_col(opcode, &opcodemap_row, &opcodemap_col);
    opcode_name = two_byte_opcodemap[opcodemap_row][opcodemap_col];
  } else {
    // NOTE: One byte opcodemap
    get_opcodemap_row_col(opcode, &opcodemap_row, &opcodemap_col);
    opcode_name = one_byte_opcodemap[opcodemap_row][opcodemap_col];
  }

  // TODO: Implement decoding for this instructions now []
  switch (opcode_name) {
    // TODO: start decoding from this instruction []
  case ADD_Eb_Gb:
    // NOTE: direction is defined in opcode itself and explained in programming
    // manual
    //  Add r/m8, r8 - means add reg byte to r/m byte
    //  here r/m is destination and reg is source
    //  Add Eb, Gb means add Gb to destination Eb
    //  byte operands regardless

    opcode = FETCH(); // get modR/M byte

    fill_instruction_mod(instruction, ADD_Eb_Gb, opcode);
    break;

  case ADD_Ev_Gv:
    opcode = FETCH();
    fill_instruction_mod(instruction, ADD_Ev_Gv, opcode);
    break;

  case ADD_Gb_Eb:
    opcode = FETCH();
    fill_instruction_mod(instruction, ADD_Gb_Eb, opcode);
    break;

  case ADD_Gv_Ev:
    opcode = FETCH();
    fill_instruction_mod(instruction, ADD_Gv_Ev, opcode);
    break;

  case ADD_AL_Ib:
    // a very simple instruction just followed by 8 bit source
    // source added with AL register into AL register
    instruction->name = ADD_AL_Ib;
    break;

  case ADD_eAX_Iv:
    instruction->name = ADD_eAX_Iv;
    break;

  case PUSH_ES:
    // only one byte instruction
    instruction->name = PUSH_ES;
    break;

  case POP_ES:
    // only one byte instruction
    instruction->name = POP_ES;
    break;

  case OR_Eb_Gb:
    opcode = FETCH();
    fill_instruction_mod(instruction, OR_Eb_Gb, opcode);
    break;

  case OR_Ev_Gv:
    opcode = FETCH();
    fill_instruction_mod(instruction, OR_Ev_Gv, opcode);
    break;

  case OR_Gb_Eb:
    opcode = FETCH();
    fill_instruction_mod(instruction, OR_Gb_Eb, opcode);
    break;

  case OR_Gv_Ev:
    opcode = FETCH();
    fill_instruction_mod(instruction, OR_Gv_Ev, opcode);
    break;
  case OR_AL_Ib:
    instruction->name = OR_AL_Ib;
    break;
  case OR_eAX_Iv:
    instruction->name = OR_eAX_Iv;
    break;

  case PUSH_CS:
    instruction->name = PUSH_CS;
    break;

  case ADC_Eb_Gb:
    opcode = FETCH();
    fill_instruction_mod(instruction, ADC_Eb_Gb, opcode);
    break;

  case ADC_Ev_Gv:
    opcode = FETCH();
    fill_instruction_mod(instruction, ADC_Ev_Gv, opcode);
    break;

  case ADC_Gb_Eb:
    opcode = FETCH();
    fill_instruction_mod(instruction, ADC_Gb_Eb, opcode);
    break;

  case ADC_Gv_Ev:
    opcode = FETCH();
    fill_instruction_mod(instruction, ADC_Gv_Ev, opcode);
    break;

  case ADC_AL_Ib:
    instruction->name = ADC_AL_Ib;
    break;

  case ADC_eAX_Iv:
    instruction->name = ADC_eAX_Iv;
    break;

  case PUSH_SS:
    instruction->name = PUSH_SS;
    break;
  case POP_SS:
    instruction->name = POP_SS;
    break;

  case SBB_Eb_Gb:
    FETCH();
    fill_instruction_mod(instruction, SBB_Eb_Gb, opcode);
    break;

  case SBB_Ev_Gv:
    FETCH();
    fill_instruction_mod(instruction, SBB_Ev_Gv, opcode);
    break;

  case SBB_Gb_Eb:
    FETCH();
    fill_instruction_mod(instruction, SBB_Gb_Eb, opcode);
    break;

  case SBB_Gv_Ev:
    FETCH();
    fill_instruction_mod(instruction, SBB_Gv_Ev, opcode);
    break;

  case SBB_AL_Ib:
    instruction->name = SBB_AL_Ib;
    break;

  case SBB_eAX_Iv:
    instruction->name = SBB_eAX_Iv;
    break;
  case PUSH_DS:
    instruction->name = PUSH_DS;
    break;
  case POP_DS:
    instruction->name = POP_DS;
    break;

  case AND_Eb_Gb:
    opcode = FETCH();
    fill_instruction_mod(instruction, AND_Eb_Gb, opcode);
    break;

  case AND_Ev_Gv:
    opcode = FETCH();
    fill_instruction_mod(instruction, AND_Ev_Gv, opcode);
    break;

  case AND_Gb_Eb:
    opcode = FETCH();
    fill_instruction_mod(instruction, AND_Gb_Eb, opcode);
    break;

  case AND_Gv_Ev:
    opcode = FETCH();
    fill_instruction_mod(instruction, AND_Gv_Ev, opcode);
    break;

  case AND_AL_Ib:
    instruction->name = AND_AL_Ib;
    break;

  case AND_eAX_Iv:
    instruction->name = AND_eAX_Iv;
    break;

  case PREFIX_SegOverride_ES:
    instruction->name = PREFIX_SegOverride_ES;
    break;

  case DAA:
    instruction->name = DAA;
    break;

  case SUB_Eb_Gb:
    opcode = FETCH();
    fill_instruction_mod(instruction, SUB_Eb_Gb, opcode);
    break;

  case SUB_Ev_Gv:
    opcode = FETCH();
    fill_instruction_mod(instruction, SUB_Ev_Gv, opcode);
    break;

  case SUB_Gb_Eb:
    opcode = FETCH();
    fill_instruction_mod(instruction, SUB_Gb_Eb, opcode);
    break;

  case SUB_Gv_Ev:
    opcode = FETCH();
    fill_instruction_mod(instruction, SUB_Gv_Ev, opcode);
    break;

  case SUB_AL_Ib:
    instruction->name = SUB_AL_Ib;
    break;

  case SUB_eAX_Iv:
    instruction->name = SUB_eAX_Iv;
    break;

  case PREFIX_SegOverride_CS:
    instruction->name = PREFIX_SegOverride_CS;
    break;

  case DAS:
    instruction->name = DAS;
    break;

  case XOR_Eb_Gb:
    opcode = FETCH();
    fill_instruction_mod(instruction, XOR_Eb_Gb, opcode);
    break;

  case XOR_Ev_Gv:
    opcode = FETCH();
    fill_instruction_mod(instruction, XOR_Ev_Gv, opcode);
    break;

  case XOR_Gb_Eb:
    opcode = FETCH();
    fill_instruction_mod(instruction, XOR_Gb_Eb, opcode);
    break;

  case XOR_Gv_Ev:
    opcode = FETCH();
    fill_instruction_mod(instruction, XOR_Gv_Ev, opcode);
    break;

  case XOR_AL_Ib:
    instruction->name = XOR_AL_Ib;
    break;

  case XOR_eAX_Iv:
    instruction->name = XOR_eAX_Iv;
    break;

  case PREFIX_SegOverride_SS:
    instruction->name = PREFIX_SegOverride_SS;
    break;

  case AAA:
    instruction->name = AAA;
    break;

  case CMP_Eb_Gb:
    opcode = FETCH();
    fill_instruction_mod(instruction, CMP_Eb_Gb, opcode);
    break;

  case CMP_Ev_Gv:
    opcode = FETCH();
    fill_instruction_mod(instruction, CMP_Ev_Gv, opcode);
    break;

  case CMP_Gb_Eb:
    opcode = FETCH();
    fill_instruction_mod(instruction, CMP_Gb_Eb, opcode);
    break;

  case CMP_Gv_Ev:
    opcode = FETCH();
    fill_instruction_mod(instruction, CMP_Gv_Ev, opcode);
    break;

  case CMP_AL_Ib:
    instruction->name = CMP_AL_Ib;
    break;

  case CMP_eAX_Iv:
    instruction->name = CMP_eAX_Iv;
    break;

  case PREFIX_SegOverride_DS:
    instruction->name = PREFIX_SegOverride_DS;
    break;

  case AAS:
    instruction->name = AAS;
    break;

  case INC_eAX:
    instruction->name = INC_eAX;
    break;

  case INC_eCX:
    instruction->name = INC_eCX;
    break;

  case INC_eDX:
    instruction->name = INC_eDX;
    break;

  case INC_eBX:
    instruction->name = INC_eBX;
    break;

  case INC_eSP:
    instruction->name = INC_eSP;
    break;

  case INC_eBP:
    instruction->name = INC_eBP;
    break;

  case INC_eSI:
    instruction->name = INC_eSI;
    break;

  case INC_eDI:
    instruction->name = INC_eDI;
    break;

  case DEC_eAX:
    instruction->name = DEC_eAX;
    break;

  case DEC_eCX:
    instruction->name = DEC_eCX;
    break;

  case DEC_eDX:
    instruction->name = DEC_eDX;
    break;

  case DEC_eBX:
    instruction->name = DEC_eBX;
    break;

  case DEC_eSP:
    instruction->name = DEC_eSP;
    break;

  case DEC_eBP:
    instruction->name = DEC_eBP;
    break;

  case DEC_eSI:
    instruction->name = DEC_eSI;
    break;

  case DEC_eDI:
    instruction->name = DEC_eDI;
    break;

  case PUSH_eAX:
    instruction->name = PUSH_eAX;
    break;

  case PUSH_eCX:
    instruction->name = PUSH_eCX;
    break;

  case PUSH_eDX:
    instruction->name = PUSH_eDX;
    break;

  case PUSH_eBX:
    instruction->name = PUSH_eBX;
    break;

  case PUSH_eSP:
    instruction->name = PUSH_eSP;
    break;

  case PUSH_eBP:
    instruction->name = PUSH_eBP;
    break;

  case PUSH_eSI:
    instruction->name = PUSH_eSI;
    break;

  case PUSH_eDI:
    instruction->name = PUSH_eDI;
    break;

  case POP_eAX:
    instruction->name = POP_eAX;
    break;

  case POP_eCX:
    instruction->name = POP_eCX;
    break;

  case POP_eDX:
    instruction->name = POP_eDX;
    break;

  case POP_eBX:
    instruction->name = POP_eBX;
    break;

  case POP_eSP:
    instruction->name = POP_eSP;
    break;

  case POP_eBP:
    instruction->name = POP_eBP;
    break;

  case POP_eSI:
    instruction->name = POP_eSI;
    break;

  case POP_eDI:
    instruction->name = POP_eDI;
    break;

  case PUSHA:
    instruction->name = PUSHA;
    break;

  case POPA:
    instruction->name = POPA;
    break;

  case BOUND_Gv_Ma:
    opcode = FETCH(); // modR/m byte
    fill_instruction_mod(instruction, BOUND_Gv_Ma, opcode);
    break;

  case ARPL_Ew_Rw:
    opcode = FETCH(); // modR/m byte
    fill_instruction_mod(instruction, ARPL_Ew_Rw, opcode);
    break;

  case PREFIX_SegOverride_FS:
    instruction->name = PREFIX_SegOverride_FS;
    break;

  case PREFIX_SegOverride_GS:
    instruction->name = PREFIX_SegOverride_GS;
    break;

  case PREFIX_Operand_Size:
    instruction->name = PREFIX_Operand_Size;
    break;

  case PREFIX_Address_Size:
    instruction->name = PREFIX_Address_Size;
    break;

  case PUSH_Iv:
    instruction->name = PUSH_Iv;
    break;

  case IMUL_GvEvIv:
    opcode = FETCH(); // modR/m byte
    fill_instruction_mod(instruction, IMUL_GvEvIv, opcode);
    break;

  case PUSH_Ib:
    instruction->name = PUSH_Ib;
    break;

  case IMUL_GvEvIb:
    opcode = FETCH(); // modR/m byte
    fill_instruction_mod(instruction, IMUL_GvEvIb, opcode);
    break;

  case INSB_Yb_DX:
    instruction->name = INSB_Yb_DX;
    break;

  case INSW__D_Yv_DX:
    instruction->name = INSW__D_Yv_DX;
    break;

  case OUTSB_DX_Xb:
    instruction->name = OUTSB_DX_Xb;
    break;

  case OUTSW__D_DX_Xv:
    instruction->name = OUTSW__D_DX_Xv;
    break;

  case JCC_JO:
    instruction->name = JCC_JO;
    break;

  case JCC_JNO:
    instruction->name = JCC_JNO;
    break;

  case JCC_JB:
    instruction->name = JCC_JB;
    break;

  case JCC_JNB:
    instruction->name = JCC_JNB;
    break;

  case JCC_JZ:
    instruction->name = JCC_JZ;
    break;

  case JCC_JNZ:
    instruction->name = JCC_JNZ;
    break;

  case JCC_JBE:
    instruction->name = JCC_JBE;
    break;

  case JCC_JNBE:
    instruction->name = JCC_JNBE;
    break;

  case JCC_JS:
    instruction->name = JCC_JS;
    break;

  case JCC_JNS:
    instruction->name = JCC_JNS;
    break;

  case JCC_JP:
    instruction->name = JCC_JP;
    break;

  case JCC_JNP:
    instruction->name = JCC_JNP;
    break;

  case JCC_JL:
    instruction->name = JCC_JL;
    break;

  case JCC_JNL:
    instruction->name = JCC_JNL;
    break;

  case JCC_JLE:
    instruction->name = JCC_JLE;
    break;

  case JCC_JNLE:
    instruction->name = JCC_JNLE;
    break;

  case IMM_Grp1_Eb_Ib:
    opcode = FETCH();
    fill_instruction_mod(instruction, IMM_Grp1_Eb_Ib, opcode);
    break;

  case IMM_Grp1_Ev_Iv:
    opcode = FETCH();
    fill_instruction_mod(instruction, IMM_Grp1_Ev_Iv, opcode);
    break;

  case IMM_Grp1_Eb_Ib_Redudant:
    // same as IMM_Grp1_Eb_Ib if curious read about it
    opcode = FETCH();
    fill_instruction_mod(instruction, IMM_Grp1_Eb_Ib, opcode);
    break;

  case Grp1_Ev_Ib:
    opcode = FETCH();
    fill_instruction_mod(instruction, Grp1_Ev_Ib, opcode);
    break;

  case TEST_Eb_Gb:
    opcode = FETCH();
    fill_instruction_mod(instruction, TEST_Eb_Gb, opcode);
    break;

  case TEST_Ev_Gv:
    opcode = FETCH();
    fill_instruction_mod(instruction, TEST_Ev_Gv, opcode);
    break;

  case XCHG_Eb_Gb:
    opcode = FETCH();
    fill_instruction_mod(instruction, XCHG_Eb_Gb, opcode);
    break;

  case XCHG_Ev_Gv:
    opcode = FETCH();
    fill_instruction_mod(instruction, XCHG_Ev_Gv, opcode);
    break;

  case MOV_Eb_Gb:
    opcode = FETCH();
    fill_instruction_mod(instruction, MOV_Eb_Gb, opcode);
    break;

  case MOV_Ev_Gv:
    opcode = FETCH();
    fill_instruction_mod(instruction, MOV_Ev_Gv, opcode);
    break;

  case MOV_Gb_Eb:
    opcode = FETCH();
    fill_instruction_mod(instruction, MOV_Gb_Eb, opcode);
    break;

  case MOV_Gv_Ev:
    opcode = FETCH();
    fill_instruction_mod(instruction, MOV_Gv_Ev, opcode);
    break;
  case MOV_Ew_Sw:
    opcode = FETCH();
    fill_instruction_mod(instruction, MOV_Ew_Sw, opcode);
    break;
  case LEA_Gv_M:
    opcode = FETCH();
    fill_instruction_mod(instruction, LEA_Gv_M, opcode);
    break;
  case MOV_Sw_Ew:
    opcode = FETCH();
    fill_instruction_mod(instruction, MOV_Sw_Ew, opcode);
    break;

  case POP_Ev:
    // TODO: see MOD/Rm restriction reg filed should be 0
    opcode = FETCH();
    fill_instruction_mod(instruction, POP_Ev, opcode);
    break;

  case NOP:
    // XCHG eAX, eAX a no operation
    instruction->name = NOP;
    break;

  case XCHG_eAX_eCX:
    instruction->name = XCHG_eAX_eCX;
    break;

  case XCHG_eAX_eDX:
    instruction->name = XCHG_eAX_eDX;
    break;

  case XCHG_eAX_eBX:
    instruction->name = XCHG_eAX_eBX;
    break;

  case XCHG_eAX_eSP:
    instruction->name = XCHG_eAX_eSP;
    break;

  case XCHG_eAX_eBP:
    instruction->name = XCHG_eAX_eBP;
    break;

  case XCHG_eAX_eSI:
    instruction->name = XCHG_eAX_eSI;
    break;

  case XCHG_eAX_eDI:
    instruction->name = XCHG_eAX_eDI;
    break;

  case CBW:
    instruction->name = CBW;
    break;

  case CWD:
    instruction->name = CWD;
    break;

  case CALL_Ap:
    instruction->name = CALL_Ap;
    break;

  case WAIT:
    instruction->name = WAIT;
    break;
  case PUSHF_Fv:
    instruction->name = PUSHF_Fv;
    break;

  case POPF_Fv:
    instruction->name = POPF_Fv;
    break;

  case SAHF:
    instruction->name = SAHF;
    break;

  case LAHF:
    instruction->name = LAHF;
    break;

  case MOV_AL_Ob:
    instruction->name = MOV_AL_Ob;
    break;

  case MOV_eAX_Ov:
    instruction->name = MOV_eAX_Ov;
    break;

  case MOV_Ob_AL:
    instruction->name = MOV_Ob_AL;
    break;

  case MOV_Ov_eAX:
    instruction->name = MOV_Ov_eAX;
    break;

  case MOVSB_Xb_Yb:
    instruction->name = MOVSB_Xb_Yb;
    break;

  case MOVSW__D_Xv_Yv:
    instruction->name = MOVSW__D_Xv_Yv;
    break;

  case CMPSB_Xb_Yb:
    instruction->name = CMPSB_Xb_Yb;
    break;

  case CMPSW__D_Xv_Yv:
    instruction->name = CMPSW__D_Xv_Yv;
    break;

  default:
    break;
  }
  return Decoder_FAIL;
}
