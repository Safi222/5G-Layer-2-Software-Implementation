#ifndef IP_PACKET_H
#define IP_PACKET_H

#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <winsock2.h>

class IpHeader {
private:
    uint8_t version : 4;
    uint8_t ihl : 4;
    uint8_t dscp : 6;
    uint8_t ecn : 2;
    uint16_t totalLength;
    uint16_t identification;
    uint16_t flags : 3;
    uint16_t fragmentOffset : 13;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t headerChecksum;
    uint32_t sourceIp;
    uint32_t destinationIp;
    std::vector<uint8_t> options;
    std::vector<uint8_t> padding;

public:
    IpHeader(uint32_t srcIp, uint32_t destIp, uint16_t dataLength, uint8_t protocol);
    void displayHeader() const;
};

class IpPacket {
private:
    IpHeader header;
    std::vector<uint8_t> data;

public:
    IpPacket(uint32_t srcIp, uint32_t destIp, uint16_t dataLength, uint8_t protocol, const std::vector<uint8_t>& data);
    void printPacketDetails() const;
};

#endif