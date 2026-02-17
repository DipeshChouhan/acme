#include <acme/i486/decoder.h>
#include <assert.h>

#define get_mod_reg_field(mod) ((mod >> 3) & 0b111)
#define get_mod_mod_field(mod) ((mod >> 6) & 0b11)
#define get_mod_rm_field(mod) (mod & 0b111)

// convert it to inline function
#define get_addressing_mode(cpu) 0

#define ADRESSING_MODE_16 0
#define ADRESSING_MODE_32 1

// NOTE: temporary fetch

#define FETCH() 0

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

  default:
    break;
  }
  return Decoder_FAIL;
}
