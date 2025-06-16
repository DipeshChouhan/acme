#ifndef ACME_i486_CPU_H
#define ACME_i486_CPU_H

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

  // global descriptor table register
  struct gdtr {
    uint32_t base_address;
    uint16_t segment_limit;
  };

  // local descriptor table register
  struct ldtr {
    uint32_t base_address;
    uint16_t segment_limit;
    uint16_t segment_selector;
  };

  // interrupt descriptor table register
  struct idtr {
    uint32_t base_address;
    uint16_t segment_limit;
  };

  // task register
  // TODO: check for descriptor attributes
  struct tr {
    uint32_t base_address;
    uint16_t segment_limit;
    uint16_t segment_selector;
    uint8_t descriptor_attributes;
  };

} Cpu;

#endif
