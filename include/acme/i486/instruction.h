#ifndef ACME_i486_INSTRUCTION_H
#define ACME_i486_INSTRUCTION_H

typedef enum InstructionType {

  INSTRUCTION, // ASCII Adjust after addition

} InstructionType;

typedef struct Instruction {
  InstructionType inst_type; // type of instruction
} Instruction;

#endif
