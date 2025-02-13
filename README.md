# 5G Layer-2 Software Implementation

This repository contains a modular implementation of key Layer-2 components for 5G networks. The project simulates the behavior of 5G protocols at the data link layer, including packet generation, header and payload processing, segmentation, reassembly, scheduling, and multiplexing. This implementation serves as a platform for understanding and testing 5G NR (New Radio) protocols.

---

## Table of Contents

- [Overview](#overview)
- [Authors](#authors)
  - [Key Components](#key-components)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)

---

## Overview

The project simulates the following key Layer-2 protocols used in 5G networks:

## Authors

1. Safia Gibril Nouman Abdalla            - 174045
2. Alaa Almouiz Farog Mohammed            - 174018
3. Ethar Abdelazeem MohamedAli Abdelgader - 174022
4. Suzan Ahmed Ali Fadlelmoula            - 174041
5. Azza Ibrahim hassan bakhit             - 174054
6. Rayan hassan khogali mohamed           - 174034
7. Marafi Muawya Sufyan Fakhruddin        - 175089
8. Safaa Abdelsalam Abdelmagid Elamin     - 174044

### Key Components

- **IP Packet Generator**:  
  Generates dummy IP packets with a header and payload to simulate network traffic.
  
- **PDCP (Packet Data Convergence Protocol)**:  
  Processes IP packets by performing header compression, encryption (AES via OpenSSL), and integrity checking (SHA-256 via EVP).
  
- **RLC (Radio Link Control)**:  
  Manages segmentation and reassembly of packets, simulating error correction and reliable data transfer.
  
- **MAC (Medium Access Control)**:  
  Packages reassembled data into transport blocks, adds MAC headers, and simulates scheduling and multiplexing for transmission.

---

## Features

- **Modular Architecture**:  
  Each protocol layer (IP, PDCP, RLC, MAC) is implemented as a separate module.
  
- **Robust Data Processing**:  
  Includes reliable segmentation/reassembly, header compression, AES encryption, and SHA-256 integrity checks.
  
- **Simulation of 5G Protocols**:  
  Provides a realistic simulation of the 5G NR Layer-2 protocol stack.
  
- **Detailed Debug Output**:  
  Prints detailed information at each layer for testing, visualization, and debugging.

---

## Requirements

- **Operating System**:  
  Windows (for Winsock2 support) or any platform with appropriate network libraries.
  
- **Compiler**:  
  A C++ compiler supporting C++11 or later (GCC, Clang, MinGW-w64, etc.).
  
- **Libraries**:
  - OpenSSL (for AES encryption and SHA-256 integrity checks)
  - Winsock2 (on Windows)
  
- **Knowledge**:  
  Basic understanding of 5G networking protocols and C++ programming.

---

## Installation

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/Safi222/5G-Layer-2-Software-Implementation.git
   cd 5G-Layer-2-Software-Implementation
   ```

2. **Install Dependencies:**
   - **OpenSSL:**  
     On Ubuntu/Debian:
     ```bash
     sudo apt-get install libssl-dev
     ```
     On macOS (using Homebrew):
     ```bash
     brew install openssl
     ```
   - **Winsock2:**  
     Included with Windows. Ensure your compiler is set up for Windows development (MinGW-w64 or Visual Studio).

3. **Build the Project:**
   Use the provided Makefile or compile manually. For example, with `g++`:
   ```bash
   g++ main.cpp IpPacketGenerator/IpPacketGenerator.cpp PDCP/PDCP.cpp RLC/RLC.cpp MAC/MAC.cpp -o 5GLayer2Project.exe -lws2_32 -lssl -lcrypto
   ```

---

## Usage

After building the project, run the executable to simulate the full 5G Layer-2 protocol stack:

```bash
./5GLayer2Project.exe
```

The program will:
- Generate a dummy IP packet.
- Process the packet through the PDCP layer (header compression, AES encryption, SHA-256 integrity check).
- Segment and reassemble the packet using the RLC layer.
- Package the data into transport blocks and schedule them via the MAC layer.
  
Console output displays detailed information from each layer for debugging and analysis.

---

## Project Structure

```
5G-Layer-2-Software-Implementation/
│
├── IpPacketGenerator/
│   ├── IpPacketGenerator.h      # Definitions for IP packet generation
│   └── IpPacketGenerator.cpp    # Implementation of IP packet generation
│
├── PDCP/
│   ├── PDCP.h                   # PDCP interface and function declarations
│   └── PDCP.cpp                 # PDCP implementation (header compression, AES encryption, SHA-256 integrity)
│
├── RLC/
│   ├── RLC.h                    # RLC interface declarations (segmentation, reassembly, retransmission)
│   └── RLC.cpp                  # RLC implementation
│
├── MAC/
│   ├── MAC.h                    # MAC interface declarations (transport block creation, scheduling)
│   └── MAC.cpp                  # MAC implementation
│
├── main.cpp                     # Main program integrating all layers
├── README.md                    # Project documentation
└── Makefile (optional)          # Build instructions (if provided)
```

---

## Contributing

Contributions are welcome! Please follow these guidelines:
- **Fork** the repository.
- **Create** a new branch for each significant change.
- **Submit** a pull request with a clear description of your changes.
- **Ensure** your code follows the project's coding style and includes appropriate documentation.

---

## License

This project is not yet licensed.
---

## Acknowledgments

- **OpenSSL**: For providing robust cryptographic libraries.
- **3GPP Specifications**: For guiding the design of 5G NR protocol simulations.
- **Course Instructors and Peers**: For support and guidance during this project.