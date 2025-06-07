#ifndef i486_CPU_H
#define i486_CPU_H

#include <stdint.h>

typedef struct Cpu {

  // general registers
  uint32_t eax, ebx, ecx, edx, esi, edi, ebp, esp;

  // segment registers
  uint16_t cs, ss, ds, es, fs, gs;

  // flags register
  uint32_t eflags;

  // instruction pointer
  uint32_t eip;
} Cpu;

#endif
