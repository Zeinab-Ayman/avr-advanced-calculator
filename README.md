# AVR Layered Advanced Calculator

A modular, bare-metal embedded C calculator system built for the **ATmega32** microcontroller. The project implements a clean **Layered Architecture** to separate low-level hardware control from application-level calculation logic.

---

## 🏗️ Layered Architecture

The software is structured into four distinct abstraction layers:

- **APP/** : Application Layer (Calculator state machine & math parser)
  - `main.c` : System entry point and periodic loop
  - `OP.c` / `OP.h` : Mathematical operation processing
- **HAL/** : Hardware Abstraction Layer
  - `LCD/` : 16x2 Character LCD Driver
  - `KPD/` : 4x4 Matrix Keypad Driver
- **MCAL/** : Microcontroller Abstraction Layer
  - `DIO/` : Register-level Digital Input/Output Driver
- **Serv/** : Service Layer
  - `STD_TYPES.h` : Fixed-width standard data types
  - `BIT_MATH.h` : Bitwise operation macros

---

## ✨ Key Features

- **Decoupled Architecture:** Strict separation between hardware register manipulation, board-level peripherals, and application algorithms.
- **Arithmetic Engine:** Processes fundamental arithmetic operations (+, -, *, /) with operand parsing and error handling.
- **Matrix Keypad Driver:** Non-blocking debouncing and key-matrix decoding for reliable user input.
- **LCD Driver:** Real-time display updates for operands, operators, and evaluated outputs.
- **MISRA-C Compliant Foundation:** Standard type abstractions and register-level bit-masking macros for high portability.

---

## 🔌 Hardware Circuit & Simulation

- **Schematic & Design:** Detailed hardware layout is available in the [assets/proteus_Design.pdf](assets/proteus_Design.pdf) file.

---

## 🎬 Demo

Here is a full demonstration of the calculator application simulation:

[<video src="assets/demo.mp4" controls="controls" style="max-width: 100%; height: auto;">
  Your browser does not support the video tag.
</video>
https://github.com/Zeinab-Ayman/avr-advanced-calculator/raw/main/assets/demo_video.mp4](https://github.com/user-attachments/assets/96802b5d-7240-4f89-aca5-00c6055f4377)

---

## 🛠️ Hardware & Environment

| Item | Specification |
| :--- | :--- |
| **Microcontroller** | Microchip AVR ATmega32 (16 MHz) |
| **Input Interface** | 4x4 Matrix Keypad |
| **Display Interface**| 16x2 Character LCD (HD44780 compatible) |
| **Language** | C (Embedded C) |
| **Toolchain** | AVR-GCC / Eclipse IDE with AVR Plugin |
| **Simulation** | Proteus VSM |

---

## 🚀 Build & Setup

### Prerequisites
- `avr-gcc` toolchain and `avr-libc`
- Eclipse IDE for C/C++ Developers (configured with AVR Eclipse Plugin) or Microchip Studio

### Compilation
1. Clone the repository:
   ```bash
   git clone https://github.com/Zeinab-Ayman/avr-advanced-calculator.git
   ```

2. Import the project into your IDE workspace:
   - File -> Open Projects from File System... -> Choose the repository directory.

3. Build the project (Ctrl + B) to produce the .hex flash binary in the output folder.
