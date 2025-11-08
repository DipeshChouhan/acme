#include <acme/i486/decoder.h>
#include <stdlib.h>

// TODO : check for opcode map and opcodes and implement opcode table in decoder

extern int one_byte_opcodemap[16][16];

extern int two_byte_opcodemap[16][16];

extern int group_opcodemap[8][8];

// TODO: implement decoder no testing required for now it's simple enough

AcmeStatus decode(Cpu *cpu, Instruction *instruction) {

  return Decoder_FAIL;
}
