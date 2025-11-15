#include <acme/i486/decoder.h>
#include <assert.h>

// NOTE: temporary fetch
#define FETCH() 0

// Dear gemini check for correctness of this function
static inline void get_opcodemap_row_col(uint8_t opcode_byte, int *row,
                                         int *col) {
  *row = opcode_byte >> 4;
  *col = opcode_byte & 0x0F;
}

// TODO : check for opcode map and opcodes and implement opcode table in decoder

extern int one_byte_opcodemap[16][16];

extern int two_byte_opcodemap[16][16];

extern int group_opcodemap[8][8];

// they are globals specific to decoder
static uint8_t opcode = 0;
static int opcodemap_row = 0;
static int opcodemap_col = 0;
static int opcode_name = 0;

// TODO: implement decoder no testing required for now it's simple enough

AcmeStatus decode(Cpu *cpu, Instruction *instruction) {
  opcode = FETCH();
  if (opcode == 0x0F) {
    // NOTE: Two byte opcodemap
    opcode = FETCH();
    get_opcodemap_row_col(opcode, &opcodemap_row,
                          &opcodemap_col); // Use the inline function
    opcode_name = two_byte_opcodemap[opcodemap_row][opcodemap_col];
  } else {
    // NOTE: One byte opcodemap
    get_opcodemap_row_col(opcode, &opcodemap_row,
                          &opcodemap_col); // Use the inline function
    opcode_name = one_byte_opcodemap[opcodemap_row][opcodemap_col];
  }

  // TODO: Implement decoding for this instructions now []
  switch (opcode_name) {
  case ADD_Eb_Gb:
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
