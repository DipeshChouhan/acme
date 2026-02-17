#ifndef ACME_i486_INSTRUCTION_H
#define ACME_i486_INSTRUCTION_H

#include <stdint.h>
typedef enum InstructionType {

  INSTRUCTION, // ASCII Adjust after addition

} InstructionType;

// NOTE: store pointers for source and destination 
typedef struct Instruction {
  InstructionType inst_type; // type of instruction
  union {
    uint8_t source_byte;
    uint32_t source_word;
    void *source_ptr;
  };

  void *destination_ptr;
} Instruction;

#endif
