#ifndef ACME_i486_INSTRUCTION_H
#define ACME_i486_INSTRUCTION_H

typedef enum InstructionType {

  INSTRUCTION, // ASCII Adjust after addition

} InstructionType;

// NOTE: store pointers for source and destination 
typedef struct Instruction {
  InstructionType inst_type; // type of instruction
} Instruction;

#endif
