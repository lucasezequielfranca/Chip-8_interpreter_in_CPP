#include <cstdint>
#include <fstream>
#include <iosfwd>
#include <iostream>

typedef struct chip8 {
  // memory is set to 4096 bytes
  uint8_t memory[4096];
  uint16_t pc;
  // 16 stack with 16 bits or 2 bytes each
  uint16_t stack[16];
  uint8_t sp;
  // 16 bits register i
  uint16_t i;
  // v0 to vF register multiple pourpose
  uint16_t vRegister[16];

  // timers run down at 60hz
  uint8_t delay_timer;
  uint8_t sound_timer;

  uint8_t display[64 * 32];

  const uint8_t FONT_SET[80] = {
      0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
      0x20, 0x60, 0x20, 0x20, 0x70, // 1
      0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
      0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
      0x90, 0x90, 0xF0, 0x10, 0x10, // 4
      0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
      0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
      0xF0, 0x10, 0x20, 0x40, 0x40, // 7
      0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
      0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
      0xF0, 0x90, 0xF0, 0x90, 0x90, // A
      0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
      0xF0, 0x80, 0x80, 0x80, 0xF0, // C
      0xE0, 0x90, 0x90, 0x90, 0xE0, // D
      0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
      0xF0, 0x80, 0xF0, 0x80, 0x80  // F
  };

  uint8_t keypad[16];

} chip8;

void initChip8(chip8 &cpu) {
  // set program counter to 512 or 0x200
  cpu.pc = 0x200;
  // initialize the font_set at 0x50 in memory
  for (int i = 0; i < 80; i++) {
    cpu.memory[0x50 + i] = cpu.FONT_SET[i];
  }
}

// need to check for 0 return before continuing with the cpu cycle, if return is
// 1 stop the program
int loadRom(chip8 &cpu, char *filename) {
  // inicia um cursor que vai receber o tamanho da rom
  std::streampos size;
  // opens the file in if mode (read mode) deafult ios is in for ifstream, opens
  // in binary, set the pointer then to the end of the file with ios::ate, this
  // is needed for dinamicly getting the size for the size var above
  std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
  if (!file.is_open()) {
    std::cout << "file could not be open" << std::endl;
    return 1;
  }
  // pass the size of the file to size cursor
  size = file.tellg();
  // set the file cursor to the beggining again
  // for the copy to work
  file.seekg(0, std::ios::beg);
  // copy the contents of the rom to the cpu memory starting at pc
  // counter (0x200), aos need to rcast the uint8_t to char* using
  // reinterpret_cast<char*>() as its expected for the read method
  file.read(reinterpret_cast<char *>(&cpu.memory[cpu.pc]), size);

  file.close();
  return 0;
}

int main(int argc, char *argv[]) {
  // initialize chip8 as CHIP8 and run initialize func
  chip8 CHIP8;
  initChip8(CHIP8);
  // run check if rom is loaded correctly
  int isNotLoaded = loadRom(CHIP8, argv[1]);
  if (isNotLoaded) {
    std::cout << "Ending program!" << std::endl;
  }
  std::cout << "Rom loaded with sucess" << std::endl;

  // continue the cycle
}
