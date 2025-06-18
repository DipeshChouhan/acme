#ifndef ACME_i486_DECODER_H
#define ACME_i486_DECODER_H

#include <acme-util/status.h>
#include <acme/i486/cpu.h>
#include <acme/i486/instruction.h>

DecoderStatus decode(Cpu *cpu, Instruction *instruction);

#endif
