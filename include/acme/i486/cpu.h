#ifndef ACME_i486_CPU_H
#define ACME_i486_CPU_H

#include <stdint.h>

// this are indexs to the registers in registers and segment_regs array

#define REG_EAX 0
#define REG_EBX 1
#define REG_ECX 2
#define REG_EDX 3
#define REG_ESI 4
#define REG_EDI 5
#define REG_EBP 6
#define REG_ESP 7

#define SEG_CS 0
#define SEG_SS 1
#define SEG_DS 2
#define SEG_ES 3
#define SEG_FS 4
#define SEG_GS 5

#define CR0 0
#define CR1 1
#define CR2 2
#define CR3 3

#define DR0 0
#define DR1 1
#define DR2 2
#define DR3 3
#define DR4 4
#define DR5 5
#define DR6 6
#define DR7 7

typedef struct InvisibleSegmentReg {
  uint32_t base_address;
  uint32_t segment_limit;
  uint8_t type;
  uint8_t other_info;
} InvSegmentReg;

typedef struct Cpu {

  // general registers
  uint32_t registers[8];

  // segment registers
  uint16_t segment_regs[6];
  // invisible parts of segment registers
  InvSegmentReg segment_regs_inv[6];

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
