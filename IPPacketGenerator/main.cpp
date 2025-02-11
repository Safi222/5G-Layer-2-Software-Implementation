#include "IpPacket.h"

int main() {
     // Define source and destination IP addresses in hex
    uint32_t sourceIp = 0xC0A80101;  // 192.168.1.1
    uint32_t destIp = 0xC0A80102;    // 192.168.1.2

    // Create sample payload data (ASCII "Hello, World! IP Pac")
    std::vector<uint8_t> sampleData = { 
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x2C, 0x20, 0x57, 
        0x6F, 0x72, 0x6C, 0x64, 0x21, 0x20, 0x49, 0x50, 
        0x20, 0x50, 0x61, 0x63 
    };


    // Create IP packet with:
    // - Source IP
    // - Destination IP
    // - Data length
    // - Protocol
    // - Payload
    IpPacket packet(sourceIp, destIp, sampleData.size(), 6, sampleData);
    
    // Display packet info
    packet.printPacketDetails();

    return 0;
}