#ifndef IP_PACKET_H
#define IP_PACKET_H

// Required header files
#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <winsock2.h>

class IpHeader {
private:
    // IP header fields using bit fields to match exact IP header structure
    uint8_t version : 4;    // IP version (4 bits for IPv4)
    uint8_t ihl : 4;    // Internet Header Length (4 bits)   
    uint8_t dscp : 6;   // Differentiated Services Code Point (6 bits)
    uint8_t ecn : 2;     // Explicit Congestion Notification (2 bits)
    uint16_t totalLength;   // Total packet length
    uint16_t identification;    // Packet identification
    uint16_t flags : 3;     // Fragmentation flags (3 bits)
    uint16_t fragmentOffset : 13;   // Fragment offset (13 bits)
    uint8_t ttl;     // Time to Live
    uint8_t protocol;   // Transport protocol
    uint16_t headerChecksum;    // Header checksum
    uint32_t sourceIp;  // Source IP address
    uint32_t destinationIp;     // Destination IP address
    std::vector<uint8_t> options;   // Optional fields
    std::vector<uint8_t> padding;   // Padding bytes

public:
    // Member function declarations
    IpHeader(uint32_t srcIp, uint32_t destIp, uint16_t dataLength, uint8_t protocol);
    void displayHeader() const;
};

class IpPacket {
private:
    IpHeader header;
    std::vector<uint8_t> data;

public:
    // Constructor and member function declarations
    IpPacket(uint32_t srcIp, uint32_t destIp, uint16_t dataLength, uint8_t protocol, const std::vector<uint8_t>& data);
    void printPacketDetails() const;
};

#endif