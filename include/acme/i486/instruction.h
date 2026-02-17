#ifndef ACME_i486_INSTRUCTION_H
#define ACME_i486_INSTRUCTION_H

#include <stdint.h>

// NOTE: It only need to show instruction type and how to access other operands
typedef struct Instruction {
  int name; // type of instruction
  uint8_t mod_field;
  uint8_t reg_field;
  uint8_t rm_field;
} Instruction;

#endif
