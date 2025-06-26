#include <acme/i486/cpu.h>

/**
 * Insitailizes the cpu with the default values when it is powered up
 * @param[out] cpu Pointer to the cpu that is filled with the default values
 * @return Nothing
 */
void power_up_cpu(Cpu *cpu) {
  cpu->eflags = 0x2;
  cpu->eip = 0x0000FFF0;
  cpu->segment_regs[SEG_CS] = 0xF000;
  cpu->segment_regs[SEG_DS] = 0x0000;
  cpu->segment_regs[SEG_ES] = 0x0000;
  cpu->segment_regs[SEG_FS] = 0x0000;
  cpu->segment_regs[SEG_GS] = 0x0000;
  cpu->segment_regs[SEG_SS] = 0x0000;
  cpu->control_regs[CR0] = 0x0000;

  cpu->idtr.base_address = 0x00000000;
  cpu->idtr.segment_limit = 0x03FF;
  cpu->debug_regs[DR7] = 0;

  // setting invisible parts of the segment registers to default values
  cpu->segment_regs_inv[SEG_CS].base_address = 0xFFFF0000;
  cpu->segment_regs_inv[SEG_CS].segment_limit = 0xFFFF;

  cpu->segment_regs_inv[SEG_DS].base_address = 0x0;
  cpu->segment_regs_inv[SEG_DS].segment_limit = 0xFFFF;
  cpu->segment_regs_inv[SEG_ES].base_address = 0x0;
  cpu->segment_regs_inv[SEG_ES].segment_limit = 0xFFFF;
}
