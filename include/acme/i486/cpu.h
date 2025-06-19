#ifndef ACME_i486_CPU_H
#define ACME_i486_CPU_H

#include <stdint.h>

typedef struct Cpu {

  // general registers
  uint32_t registers[8];

  // segment registers
  uint16_t segment_regs[6];

  // flags register
  uint32_t eflags;

  // instruction pointer
  uint32_t eip;

  // control registers
  uint32_t control_regs[4];

  // debug registers
  uint32_t debug_regs[8];

  // memory management registers

  // global descriptor table register
  struct gdtr {
    uint32_t base_address;
    uint16_t segment_limit;
  } gdtr;

  // local descriptor table register
  struct ldtr {
    uint32_t base_address;
    uint16_t segment_limit;
    uint16_t segment_selector;
  } ldtr;

  // interrupt descriptor table register
  struct idtr {
    uint32_t base_address;
    uint16_t segment_limit;
  } idtr;

  // task register
  // TODO: check for descriptor attributes
  struct tr {
    uint32_t base_address;
    uint16_t segment_limit;
    uint16_t segment_selector;
    uint8_t descriptor_attributes;
  } tr;

} Cpu;

void power_up_cpu(Cpu *cpu);

#endif
