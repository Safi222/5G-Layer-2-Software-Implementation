# 5G Layer-2 Software Implementation

This repository contains the implementation of various Layer-2 components for a 5G network, focusing on the Radio Link Control (RLC), Medium Access Control (MAC), Packet Data Convergence Protocol (PDCP), and network packet processing. The components simulate the behavior of a 5G network's data link layer, providing a foundation for understanding and testing 5G protocols.

## Table of Contents

- [5G Layer-2 Software Implementation](#5g-layer-2-software-implementation)
  - [Table of Contents](#table-of-contents)
  - [Authors](#authors)
  - [Overview](#overview)
    - [Key Components](#key-components)
  - [Features](#features)
  - [Requirements](#requirements)
  - [Installation](#installation)

## Authors

- Safia Gibril Nouman Abdalla 174045
- Alaa Almouiz Farog Mohammed 174018

## Overview

This project simulates key Layer-2 protocols for 5G networks, including IP packet generator, the Radio Link Control (RLC), Medium Access Control (MAC), and Packet Data Convergence Protocol (PDCP). The implementation is modular, allowing easy extension and modification for future 5G protocol features. 

### Key Components

- **IP packet generator**: Generates Dummy IP packets.
- **RLC (Radio Link Control)**: Handles the reliable transfer of data between devices in the 5G network, including segmentation, reassembly, and error correction.
- **MAC (Medium Access Control)**: Manages access to the shared communication medium, ensuring data is transmitted efficiently between devices.
- **PDCP (Packet Data Convergence Protocol)**: Provides data compression and header compression, improving data transmission efficiency for 5G applications.

## Features

- RLC, MAC, and PDCP Layer-2 protocol implementations
- Reliable data transmission with error correction and segmentation
- Efficient medium access management and packet scheduling
- Data compression and header compression for optimized 5G performance
- Detailed protocol information display for testing and visualization

## Requirements

- C++ compiler (GCC/MinGW-w64)
- Basic knowledge of 5G networking protocols
- Windows operating system (for Winsock2 support)

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/Safi222/5G-Layer-2-Software-Implementation.git
   cd 5G-Layer-2-Software-Implementation
