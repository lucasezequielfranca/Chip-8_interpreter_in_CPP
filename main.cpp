#include "chip8.h"

int main(int argc, char *argv[]) {
  Chip8 cpu;
  cpu.initialize();
  cpu.load_rom(argv[1]);
}
