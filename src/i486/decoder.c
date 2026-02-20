#include "acme-util/acme_status.h"
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

extern OpcodeEntry one_byte_opcodemap[16][16];

extern OpcodeEntry two_byte_opcodemap[16][16];

extern int group_opcodemap[8][8];

// they are globals specific to decoder
static int opcode = 0;
static int opcodemap_row = 0;
static int opcodemap_col = 0;
// static int opcode_name = 0;

// TODO: implement decoder no testing required for now it's simple enough
// NOTE: A decoder should be simple as it don't have to calcluate effective
// address or any operands
// it better left to execution unit

AcmeStatus decode(Cpu *cpu, Instruction *instruction) {

  // Temporary variable to hold different mod fields
  uint32_t tmp_reg = 0;
  OpcodeEntry opcode_entry = {0};
  opcode = FETCH();

  if (opcode == 0x0F) {
    // NOTE: Two byte opcodemap
    opcode = FETCH();
    get_opcodemap_row_col(opcode, &opcodemap_row, &opcodemap_col);
    opcode_entry = two_byte_opcodemap[opcodemap_row][opcodemap_col];
  } else {
    // NOTE: One byte opcodemap
    get_opcodemap_row_col(opcode, &opcodemap_row, &opcodemap_col);
    opcode_entry = one_byte_opcodemap[opcodemap_row][opcodemap_col];
  }

  if (opcode_entry.has_modrm) {
    // NOTE: ModR/M byte
    opcode = FETCH();
    fill_instruction_mod_only(instruction, opcode);
  } else {
    instruction->name = opcode_entry.opcode;
  }
  if (instruction->name == InvalidOp){
    return Decoder_FAIL;
  }

  return Decoder_SUCCESS;
}
