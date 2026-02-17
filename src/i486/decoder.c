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

// TODO : check for opcode map and opcodes and implement opcode table in decoder []

extern int one_byte_opcodemap[16][16];

extern int two_byte_opcodemap[16][16];

extern int group_opcodemap[8][8];

// they are globals specific to decoder
static int opcode = 0;
static int opcodemap_row = 0;
static int opcodemap_col = 0;
static int opcode_name = 0;

// TODO: implement decoder no testing required for now it's simple enough

AcmeStatus decode(Cpu *cpu, Instruction *instruction) {

  // Temporary variable to hold different mod fields
  int tmp_reg_field = 0; 
  int tmp_mod_field = 0;
  int tmp_rm_field = 0;
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
    //NOTE: direction is defined in opcode itself and explained in programming manual
    // Add r/m8, r8 - means add reg byte to r/m byte
    // here r/m is destination and reg is source
    // Add Eb, Gb means add Gb to destination Eb
    // byte operands regardless

    //NOTE: Here E represents modR/M byte following opcode
    opcode = FETCH(); // fetch modR/M byte

    tmp_reg_field = get_mod_reg_field(opcode); // reg field
    tmp_mod_field = get_mod_mod_field(opcode); // mod field
    tmp_rm_field = get_mod_rm_field(opcode); // rm field
    // Can be AH, CH, DH, BH
    if (tmp_reg_field > 3) {
      tmp_reg = cpu->registers[tmp_reg_field % 4];
      instruction->source_byte = (tmp_reg >> 8) & 0xFF;
    } else {
      // Can be AL, CL, DL, BL
      tmp_reg = cpu->registers[tmp_reg_field];
      instruction->source_byte = tmp_reg & 0xFF;
    }

    if (tmp_mod_field == 0b11) {
      // register mode
      // rm shows the destination
      
      // TODO: need to know which 8-bit register it points to like in EAX AL or AH
      instruction->destination_ptr = &cpu->registers[tmp_rm_field % 4];
    } else if (tmp_mod_field == 0b00) {
      // memory mode no displacement follows

    }


    assert("not implemented");
    break;

  case ADD_Ev_Gv:
    assert("not implemented");
    break;

  case ADD_Gb_Eb:
    assert("not implemented");
    break;

  case ADD_Gv_Ev:
    assert("not implemented");
    break;

  case ADD_AL_Ib:
    assert("not implemented");
    break;

  case ADD_eAX_Iv:
    assert("not implemented");
    break;

  case PUSH_ES:
    assert("not implemented");
    break;

  case POP_ES:
    assert("not implemented");
    break;

  case OR_Eb_Gb:
    assert("not implemented");
    break;

  case OR_Ev_Gv:
    assert("not implemented");
    break;

  default:
    break;
  }
  return Decoder_FAIL;
}
