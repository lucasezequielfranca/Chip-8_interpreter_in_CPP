# chip8 Interpreter

A simple CHIP-8 interpreter written in C++ and SDL2 for graphics. Made to study emulation, low-level concepts, and how a CPU cycle works. The interpreter was tested with Timendius chip8 test suit, wich is included in roms folder.

The interpreter runs with default CHIP-8 resolutin but have the super-chip quirks enabled as it is required for most games.

---

* **Instruction Cycle (Fetch-Decode-Execute):** Basic cycle implemented, running instructions straight from memory.
* **Clock Sync:** The Cycle runs freely inside a batch of instructions per frame (~700 Hz), while the Timers and the screen renderer run locked at 60 Hz using `std::chrono`.
* **Tests passeds:**

---

## 🛠️ Bugs & Lessons Learned

Building an emulator can be tricky because a single misaligned bit breaks the entire game without causing a compilation error—it just shows weird behavior on screen. The main issues I spent time debugging were:

### 1. Decoding the `0xE000` Family
The *Corax+* ROM kept freezing or printing unknown opcodes (`EE9E`, `E0A1`) in the terminal whenever it tried to check the keypad inputs.
* **The Problem:** I was trying to validate the full 16-bit opcode inside the inner switch block. In CHIP-8, the lower byte (`NN`) is what actually defines if the command skips when a key is pressed or released, while the second nibble (`X`) changes constantly because it is just a register index.
* **The Solution:** I adjusted the inner switch under `case 0xE` to isolate strictly the final byte using `opcode & 0x00FF`. This allowed the emulator to ignore whichever register was being targeted during decoding, making the keypad skip conditions work perfectly.

### 2. Screen Loop Synchronization (Broken Frames)
When navigating through the test menus, old sprites would smear across the new ones, turning the screen into a messy blob of active pixels.
* **The Problem:** I had placed the SDL window update function (`display.update_screen`) inside the `for` loop that executes the CPU micro-cycles. Because CHIP-8 clears the screen (`00E0`) and draws multiple sprites in sequence very rapidly, SDL would render the screen mid-process, before the frame was fully put together by the CPU.
* **The Solution:** I moved the rendering call outside of the instruction loop. Now the CPU processes the whole batch of cycles for that frame in background memory first, and SDL only pushes the final result to the window once every 16.6ms (60 Hz).

---

## 🕹️ Test Status

* **Pong:** Fully functional and playable. The ball bounces correctly off the paddles because the `VF` collision detection fixed the smearing/trails.
* **Octo Quirks Test:** Passing all checks on the modern behavior screen (with Shift, Memory, and Jump flags enabled).

---

## 🔧 How to Compile and Run

### Dependencies
You need a working compiler with C++17 support and the **SDL2** library installed on your system.
I've only tested in arch linux, so windows support may not be working
