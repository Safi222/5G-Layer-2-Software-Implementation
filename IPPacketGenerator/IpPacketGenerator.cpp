#include "IpPacketGenerator.h"
#include <iomanip>
#include <cstdlib>

// IpHeader constructor
IpHeader::IpHeader(uint32_t srcIp, uint32_t destIp, uint16_t dataLength, uint8_t protocol) {
    version = 4;    // Set IPv4
    ihl = 5;    // Header length in 32-bit words (5 * 4 = 20 bytes)
    dscp = 0;   // Default service type
    ecn = 0;    // No congestion
    totalLength = htons(sizeof(IpHeader) + dataLength);  // Convert to network byte order
    identification = 0;    // Packet identifier
    flags = 0;  // No fragmentation
    fragmentOffset = 0;     // No offset
    ttl = 64;   // Time to live value
    this->protocol = protocol;      // Set transport protocol
    headerChecksum = 0;     // Initialize checksum
    sourceIp = srcIp;       // Set source IP
    destinationIp = destIp;    // Set destination IP 
}

void IpHeader::displayHeader() const {
    // Print all header fields with suitable formatting
    std::cout << "IP Header:\n";
    std::cout << "Version: " << +version 
              << ", IHL: " << +ihl 
              << ", DSCP: " << +dscp 
              << ", ECN: " << +ecn << "\n";
    std::cout << "Total Length: " << totalLength << "\n";
    std::cout << "Identification: " << identification << "\n";
    std::cout << "Flags: " << +flags 
              << ", Fragment Offset: " << fragmentOffset << "\n";
    std::cout << "TTL: " << +ttl 
              << ", Protocol: " << +protocol << "\n";
    std::cout << "Source IP: " << std::hex << sourceIp 
              << ", Destination IP: " << destinationIp << std::dec << "\n";
}

IpPacket::IpPacket(uint32_t srcIp, uint32_t destIp, uint16_t dataLength, 
                   uint8_t protocol, const std::vector<uint8_t>& data)
    : header(srcIp, destIp, dataLength, protocol),  // Initialize header
    data(data) {}

// Print packet details
void IpPacket::printPacketDetails() const {
    header.displayHeader();
    std::cout << "Payload Size: " << data.size() << " bytes\n";
    std::cout << "Payload (first 16 bytes): ";
    for (size_t i = 0; i < std::min(data.size(), size_t(16)); ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') 
                  << +data[i] << " ";
    }
    std::cout << std::dec << "\n";
}

//format the packet to "Header|Payload"
std::string IpPacket::formatPacket() const {
    std::ostringstream packetStream;

    // Format header as a simple string (just an example, adjust as needed)
    packetStream << "Version: " << +header.version << "|"
                 << "Source IP: " << std::hex << header.sourceIp << "|"
                 << "Destination IP: " << std::hex << header.destinationIp;

    // Add payload data (first 16 bytes for simplicity)
    packetStream << "|";
    for (size_t i = 0; i < std::min(data.size(), size_t(16)); ++i) {
        packetStream << std::hex << std::setw(2) << std::setfill('0') << +data[i];
    }

    return packetStream.str();
}