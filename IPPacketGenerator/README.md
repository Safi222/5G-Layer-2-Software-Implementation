# IP Packet Generator

A C++ implementation of an IPv4 packet generator that creates and displays IP packets with headers and payload data.

# The structure of an IP packet

![IP Packet Structure implemented](assets\IpPacket.png)

1. Version: This field indicates the IP protocol version, such as IPv4 or IPv6, which helps determine how the packet should be routed.
2. Total length: Specifies the packet's total length of the data payload (the message) and the header, which are essential for the recipient to understand the packet's contents.
3. Protocol: Determines the high-level protocol, like TCP, UDP, etc., used in the data payload.
4. Time to Live (TTL): Used to prevent packets from circulating indefinitely, which could cause network congestion. Every time a packet gets forwarded, the router decreases the TTL by one, and when the TTL becomes zero, the packet gets discarded, helping to avoid congestion.
5. Source IP address: Specifies the IP address of the device that sent the packet. It’s used to reply to the sender, and if a router cannot send the packet to the following location, it sends a message to the source using the source IP address to indicate the problem.
6. Destination IP address: Identifies the IP address of the intended recipient of the packet. Routers use it to determine where to forward the packet to reach its final destination.

## Features

- IPv4 header creation with all standard fields
- Customizable source and destination IP addresses
- Support for variable-length payload data
- Detailed packet information display

## Requirements

- C++ compiler (GCC/MinGW-w64)
- Basic knowledge of IP networking

## Installation

1. Clone the repository:

```bash

git clone https://github.com/Safi222/5G-Layer-2-Software-Implementation.git
cd ip-packet-generator
