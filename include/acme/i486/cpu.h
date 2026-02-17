#ifndef ACME_i486_CPU_H
#define ACME_i486_CPU_H

#include <endian.h>
#include <stdint.h>

// this are indexs to the registers in registers and segment_regs array

//
// General-Purpose 32-bit Registers (x86)
//
#define REG_EAX 0 // Accumulator
#define REG_EBX 1 // Base
#define REG_ECX 2 // Counter
#define REG_EDX 3 // Data
#define REG_ESI 4 // Source Index
#define REG_EDI 5 // Destination Index
#define REG_EBP 6 // Base Pointer
#define REG_ESP 7 // Stack Pointer

//
// Segment Registers (x86)
//
#define SEG_CS 0 // Code Segment
#define SEG_SS 1 // Stack Segment
#define SEG_DS 2 // Data Segment
#define SEG_ES 3 // Extra Segment
#define SEG_FS 4 // Extra Segment
#define SEG_GS 5 // Extra Segment

//
// Control Registers (x86)
//
#define CR0 0 // System control flags
#define CR1 1 // Reserved
#define CR2 2 // Page Fault Linear Address (PFLA)
#define CR3 3 // Page Directory Base Register (PDBR)

//
// Debug Registers (x86)
//
#define DR0 0 // Linear Breakpoint Address 0
#define DR1 1 // Linear Breakpoint Address 1
#define DR2 2 // Linear Breakpoint Address 2
#define DR3 3 // Linear Breakpoint Address 3
#define DR4 4 // Reserved
#define DR5 5 // Reserved
#define DR6 6 // Debug Status
#define DR7 7 // Debug Control

/**
 * @brief Represents the invisible (cached) part of a segment register.
 *
 * In protected mode, each segment register (CS, DS, SS, etc.) has a visible
 * 16-bit selector and an invisible descriptor cache containing the base
 * address, limit, and access rights for the segment. This struct models that
 * cache.
 */
typedef struct InvisibleSegmentReg {
  uint32_t base_address;  ///< The 32-bit linear base address of the segment.
  uint32_t segment_limit; ///< The 20-bit segment limit.
  uint8_t type;           ///< Segment type (e.g., code, data, stack).
  uint8_t
      other_info; ///< Other attributes (e.g., DPL, Present bit, Granularity).
} InvSegmentReg;

/**
 * @brief Represents the state of an x86 CPU.
 *
 * This structure holds the complete state of a CPU, including general-purpose
 * registers, segment registers (both visible and invisible parts), control
 * registers, and memory management registers. It is intended for use in an
 * emulator or virtual machine.
 */
typedef struct Cpu {

  // --- General Purpose Registers ---
  uint32_t registers[8]; ///< EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI


  // --- Segment Registers ---
  uint16_t segment_regs[6];          ///< CS, SS, DS, ES, FS, GS (selectors)
  InvSegmentReg segment_regs_inv[6]; ///< Invisible cache for segment registers

  // --- Program Status and Control ---
  uint32_t eflags; ///< The 32-bit EFLAGS register.
  uint32_t eip;    ///< The 32-bit instruction pointer.

  // --- Control Registers ---
  uint32_t control_regs[4]; ///< CR0, CR1, CR2, CR3

  // --- Debug Registers ---
  uint32_t debug_regs[8]; ///< DR0, DR1, DR2, DR3, DR4, DR5, DR6, DR7

  // --- Memory Management Registers ---

  /**
   * @brief Global Descriptor Table Register (GDTR).
   * Holds the base address and limit of the GDT.
   */
  struct gdtr {
    uint32_t base_address;  ///< Base address of the Global Descriptor Table.
    uint16_t segment_limit; ///< Limit of the Global Descriptor Table.
  } gdtr;

  /**
   * @brief Local Descriptor Table Register (LDTR).
   * Holds the segment selector, base address, and limit for the LDT.
   */
  struct ldtr {
    uint32_t base_address;     ///< Base address of the Local Descriptor Table.
    uint16_t segment_limit;    ///< Limit of the Local Descriptor Table.
    uint16_t segment_selector; ///< Segment selector for the LDT.
  } ldtr;

  /**
   * @brief Interrupt Descriptor Table Register (IDTR).
   * Holds the base address and limit of the IDT.
   */
  struct idtr {
    uint32_t base_address;  ///< Base address of the Interrupt Descriptor Table.
    uint16_t segment_limit; ///< Limit of the Interrupt Descriptor Table.
  } idtr;

  /**
   * @brief Task Register (TR).
   * Holds the segment selector, base address, limit, and attributes for the
   * current task state segment (TSS).
   */
  struct tr {
    uint32_t base_address;         ///< Base address of the Task State Segment.
    uint16_t segment_limit;        ///< Limit of the Task State Segment.
    uint16_t segment_selector;     ///< Segment selector for the TSS.
    uint8_t descriptor_attributes; ///< Access rights and other attributes.
  } tr;

} Cpu;

/**
 * @brief Initializes the CPU state to its power-on reset values.
 *
 * This function sets all registers and flags in the provided Cpu struct
 * to the state they would be in immediately after a hardware reset.
 * @param cpu A pointer to the Cpu struct to be initialized.
 */
void power_up_cpu(Cpu *cpu);

#endif
