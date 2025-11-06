#include <acme/i486/decoder.h>
#include <stdlib.h>

// TODO : check for opcode map and opcodes and implement opcode table in decoder

extern int one_byte_opcodemap[16][16];

extern int two_byte_opcodemap[16][16];

extern int group_opcodemap[8][8];

// NOTE: I am assuming all instructions in a single contigous memory for now
// and for testing of decoder I am creating a array containing all instructions
// for now

// TODO: get instructions 
static uint8_t *instructions = NULL;
static int eip = 0; // temporary eip

// a temporary init for decoder
void init_decoder(uint8_t *instructions, int size) {

  // initialize instructions
}


// TODO: implement decoder []

AcmeStatus decode(Cpu *cpu, Instruction *instruction) {

  return Decoder_FAIL;
}
