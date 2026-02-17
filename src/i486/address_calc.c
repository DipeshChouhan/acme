#include <acme/i486/decoder.h>
#include <stdint.h>

// the operand that address pionts to must be 8 bit [b]
// NOTE: it calculates effective address of destination operand and mod can't be (11) register mode
// real mode only
int32_t get_dest_addr_b(int mod_field, int rm_field) {


  switch(mod_field) {

    case 0b00:
      // memory addressing mode with no displacement
      switch (rm_field) {
        case 0b000:
          break;
        case 0b001:
          break;
        case 0b010:
          break;
        case 0b011:
          break;
        case 0b100:
          break;
        case 0b101:
          break;
        case 0b110:
          break;
        default:
          // 0b111
          break;
      }

      break;

    case 0b01:
      break;
    default:
      // 0b10
      break;
  }

}



