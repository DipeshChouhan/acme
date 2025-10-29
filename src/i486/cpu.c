#include <acme/i486/cpu.h>

/**
 * @brief Initializes the CPU state to its power-on defaults.
 *
 * This function sets the CPU registers to the values they would have
 * immediately after a hardware reset (power-up). This typically puts
 * the CPU in 16-bit Real Mode, ready to execute the BIOS.
 *
 * @param cpu A pointer to the Cpu structure to be initialized.
 */

void power_up_cpu(Cpu *cpu) {
  // EFLAGS register is initialized with bit 1 set; all other defined flags are
  // clear.
  cpu->eflags = 0x2;

  // After reset, execution begins at the reset vector.
  // The physical address is formed by CS_base + EIP.
  // CS selector is 0xF000, and EIP is 0xFFF0.
  // The base address for CS is set to 0xFFFF0000 (see below).
  // Physical Address = 0xFFFF0000 + 0xFFF0 = 0xFFFFFFF0.
  cpu->eip = 0x0000FFF0;
  cpu->segment_regs[SEG_CS] = 0xF000;

  // Data, Extra, and Stack segment registers are cleared.
  cpu->segment_regs[SEG_DS] = 0x0000;
  cpu->segment_regs[SEG_ES] = 0x0000;
  cpu->segment_regs[SEG_FS] = 0x0000;
  cpu->segment_regs[SEG_GS] = 0x0000;
  cpu->segment_regs[SEG_SS] = 0x0000;

  // Control Register 0 (CR0) is cleared, which means the CPU
  // starts in Real Mode (Protection Enable bit PE=0).
  cpu->control_regs[CR0] = 0x0000;

  // Initialize Interrupt Descriptor Table Register (IDTR).
  // Default real-mode values: base at 0, limit of 0x3FF (1KB).
  cpu->idtr.base_address = 0x00000000;
  cpu->idtr.segment_limit = 0x03FF;

  // Clear Debug Register 7 (DR7), disabling all hardware breakpoints.
  cpu->debug_regs[DR7] = 0;

  // Set the "hidden" or "descriptor cache" parts of the segment registers
  // to their default power-on values. In protected mode, these are loaded
  // from descriptor tables, but on reset, they have fixed values.

  // Code Segment (CS) base is set to access the top of the 4GB address space.
  // This is a special case for the reset vector.
  cpu->segment_regs_inv[SEG_CS].base_address = 0xFFFF0000;
  cpu->segment_regs_inv[SEG_CS].segment_limit = 0xFFFF; // 64KB limit

  // Other segments default to a base of 0 and a 64KB limit.
  cpu->segment_regs_inv[SEG_DS].base_address = 0x0;
  cpu->segment_regs_inv[SEG_DS].segment_limit = 0xFFFF;
  cpu->segment_regs_inv[SEG_ES].base_address = 0x0;
  cpu->segment_regs_inv[SEG_ES].segment_limit = 0xFFFF;
}
