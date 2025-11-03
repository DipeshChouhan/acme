#include <acme/i486/decoder.h>

// TODO : check for opcode map and opcodes and implement opcode table in decoder

int onebyte_opcode_map[0xF][0xF] = {{}};

DecoderStatus decode(Cpu *cpu, Instruction *instruction) {
  return Decoder_FAIL;
}
