# B31DG-ESP32-C3-Project
📂 B31DG-Assignment-1
│── 📂 main          # Source code for Arduino and ESP-IDF
│   ├── sri_patnala.c      # ESP-IDF C code
│   ├── sri_patnala_arduino.ino   # Arduino code
│   │── .gitignore  # Exclude build files, logs, etc.
│   ├── CMakeLists.txt # ESP-IDF build configuration
│   ├──idf_component.yml
│   ├──Kconfig.projbuild
│   ├──sdkconfig
│── .gitignore      # Exclude build files, logs, etc.
│── 📂 docs         # Documentation and report
│   ├── B31DG-Assignment-1-<StudentNumber>.pdf
│── README.md       # Explains repository structure


# **ESP32-C3-WROOM-02U Waveform Generator**

This project demonstrates how to use the ESP32-C3-WROOM-02U microcontroller to generate waveforms based on user input from push buttons. The project includes both a normal waveform and an alternative waveform, with timing parameters derived from a surname-based algorithm.

---

## **Table of Contents**
1. [Project Overview](#project-overview)
2. [Hardware Requirements](#hardware-requirements)
3. [Software Requirements](#software-requirements)
4. [Setup Instructions](#setup-instructions)
   - [Arduino IDE Setup](#arduino-ide-setup)
   - [ESP-IDF in VSCode Setup](#esp-idf-in-vscode-setup)
5. [Running the Project](#running-the-project)
   - [Using Arduino IDE](#using-arduino-ide)
   - [Using ESP-IDF in VSCode](#using-esp-idf-in-vscode)
6. [Code Explanation](#code-explanation)
7. [Troubleshooting](#troubleshooting)
8. [License](#license)

---

## **Project Overview**
The project generates two types of waveforms:
1. **Normal Waveform**: A sequence of pulses with increasing ON time and fixed OFF time.
2. **Alternative Waveform**: Four variations based on a selection rule derived from a surname-based algorithm.

The waveform generation is controlled by two push buttons:
- **PB1**: Enables/disables the output.
- **PB2**: Toggles between normal and alternative waveforms.

---

## **Hardware Requirements**
- ESP32-C3-WROOM-02U microcontroller
- 2x Push buttons
- 1x Red LED (for DATA signal)
- 1x Green LED (for SYNC signal)
- Resistors (for LEDs and push buttons)
- Breadboard and jumper wires
- USB cable for programming and power

---

## **Software Requirements**
- Arduino IDE or VSCode with ESP-IDF extension
- ESP32 board support package (for Arduino IDE)
- ESP-IDF framework (for VSCode)
- Serial terminal (e.g., Arduino Serial Monitor, `screen`, or `idf.py monitor`)

---

## **Setup Instructions**

### **Arduino IDE Setup**
1. **Install Arduino IDE**:
   - Download and install the [Arduino IDE](https://www.arduino.cc/en/software).

2. **Add ESP32 Board Support**:
   - Open Arduino IDE and go to `File > Preferences`.
   - In the "Additional Boards Manager URLs" field, add:
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
   - Go to `Tools > Board > Boards Manager`, search for `esp32`, and install the `ESP32` package.

3. **Select Board**:
   - Go to `Tools > Board` and select `ESP32C3 Dev Module`.
   - Set the upload speed to `921600` and the port to the appropriate COM port.

4. **Upload Code**:
   - Open the provided `.ino` file in Arduino IDE.
   - Click the "Upload" button to compile and upload the code to the ESP32-C3.

---

### **ESP-IDF in VSCode Setup**
1. **Install VSCode**:
   - Download and install [Visual Studio Code](https://code.visualstudio.com/).

2. **Install ESP-IDF Extension**:
   - Open VSCode and go to the Extensions Marketplace.
   - Search for `ESP-IDF` and install the extension by Espressif Systems.

3. **Set Up ESP-IDF**:
   - Follow the on-screen instructions to install the ESP-IDF framework and tools.
   - Select the ESP32-C3 as the target chip during setup.

4. **Open Project**:
   - Clone or download this project repository.
   - Open the project folder in VSCode.

5. **Build and Flash**:
   - Open the command palette (`Ctrl+Shift+P`) and select `ESP-IDF: Build, Flash, and Monitor`.
   - The code will be compiled, flashed to the ESP32-C3, and the serial monitor will open.

---

## **Running the Project**

### **Using Arduino IDE**
1. Connect the ESP32-C3 to your computer via USB.
2. Open the `.ino` file in Arduino IDE.
3. Select the correct board and port under `Tools`.
4. Click the "Upload" button to flash the code.
5. Open the Serial Monitor (`Ctrl+Shift+M`) to view debug output.

### **Using ESP-IDF in VSCode**
1. Open the project folder in VSCode.
2. Use the command palette (`Ctrl+Shift+P`) to select `ESP-IDF: Build, Flash, and Monitor`.
3. The code will be compiled, flashed, and the serial monitor will open automatically.

---

## **Code Explanation**
The code is divided into the following sections:
1. **Pin Definitions**: Defines the pins for push buttons and LEDs.
2. **State Variables**: Tracks the state of the output and waveform selection.
3. **Timing Parameters**: Defines the timing for the waveform generation.
4. **Setup Function**: Initializes pins and serial communication.
5. **Loop Function**: Handles button presses and waveform generation.
6. **Waveform Functions**:
   - `normal_waveform()`: Generates the normal waveform.
   - `alternative_waveform()`: Generates one of four alternative waveforms based on the selection rule.

---

## **Troubleshooting**
1. **Upload Issues**:
   - Ensure the correct board and port are selected.
   - Check the USB cable and connections.

2. **Serial Monitor Issues**:
   - Ensure the baud rate is set to `115200`.
   - Restart the ESP32-C3 if the monitor does not display output.

3. **Button Bouncing**:
   - Add debouncing logic if the buttons behave erratically.

4. **LEDs Not Lighting**:
   - Check the wiring and resistor values for the LEDs.

---

## **License**
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## **Acknowledgments**
- Thanks to Espressif for the ESP32-C3 microcontroller and development tools.
- Inspired by waveform generation techniques and surname-based algorithms.

---

For any questions or issues, please open an issue in the repository or contact the project maintainer. Happy coding! 🚀
