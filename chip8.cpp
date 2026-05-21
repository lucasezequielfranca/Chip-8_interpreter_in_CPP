#include "chip8.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <ostream>

Chip8::Chip8() {
  memory.fill(0);
  pc = 0;
  i = 0;
  stack.fill(0);
  v_register.fill(0);
  delay_timer = 0;
  sound_timer = 0;
  display.fill(0);
}
Chip8::~Chip8() {}

void Chip8::initialize() {
  pc = 0x200;
  std::copy(std::begin(FONT_SET), std::end(FONT_SET), &memory[0x50]);

  std::cout << "Interpreter initialized with sucess" << std::endl;
}

uint8_t Chip8::load_rom(char *filename) {
  std::ifstream rom(filename, std::ios::in | std::ios::binary | std::ios::ate);
  if (!rom.is_open()) {
    std::cout << "Could not open rom" << filename << std::endl;
    return 1;
  }
  uint16_t size = rom.tellg();
  rom.seekg(std::ios::beg);

  rom.read(reinterpret_cast<char *>(&memory[pc]), size);

  rom.close();
  std::cout << "Rom loaded with sucess" << std::endl;
  return 0;
}

void Chip8::execute_cycle() {
  uint16_t opcode = (memory[pc] << 8) | memory[pc + 1];
  pc += 2;

  uint8_t type = (opcode & 0xF000) >> 12;
}
