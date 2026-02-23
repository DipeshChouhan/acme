#ifndef ACME_i486_MEMORY_H
#define ACME_i486_MEMORY_H

#include <stdint.h>
// NOTE: 02000000 - FFEFFFFF is unused and returns 0xFF
typedef struct Memory {

  uint8_t *main_ram; // 00000000 - 0009FFFF
  uint8_t *video_ram; // 000A0000 - 000BFFFF
  uint8_t *uma; // 000C0000 - 000FFFFF
  uint8_t *extended_ram; // 00100000 - 001FFFFF
  uint8_t *high_bios; // FFF00000 - FFFFFFFF
} Memory;


void memory_init(Memory *mem);

// TODO check for A20 game enabled or disabled to do memory wrap around
static inline uint8_t mem_read_byte(Memory *mem, uint32_t address) {
  return 0;
}

static inline void mem_write_byte(Memory *mem, uint32_t address, uint8_t value) {
  
}

static inline uint16_t mem_read_word(Memory *mem, uint32_t address) {
  return 0;
}

static inline void mem_write_word(Memory *mem, uint32_t address, uint16_t value) {
  
}

static inline uint32_t mem_read_dword(Memory *mem, uint32_t address) {
  return 0;
}

static inline void mem_write_dword(Memory *mem, uint32_t address, uint32_t value) {
  
}


#endif
