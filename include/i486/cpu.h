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

  // control registers
  uint32_t cr0, cr1, cr2, cr3;

  // debug registers
  uint32_t dr0, dr1, dr2, dr3, dr4, dr5, dr6, dr7;
  // memory management registers
} Cpu;

#endif
