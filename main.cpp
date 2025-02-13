#include <iostream>
#include <vector>
#include <cstdint>
#include "IpPacketGenerator/IpPacketGenerator.h" // Contains IpPacket and IpHeader definitions, plus formatPacket()
#include "PDCP/PDCP.h"
#include "RLC/RLC.h"
#include "MAC/MAC.h"

// Utility function to print data in hexadecimal format
void printData(const std::vector<uint8_t>& data) {
    for (auto byte : data) {
        printf("%02x ", byte);
    }
    printf("\n");
}

int main() {
    /////////////
    // Step 1: Generate an IP packet using the IP layer
    // Define some example payload data.
    std::vector<uint8_t> payload = {0x01, 0x02, 0x03, 0x04, 0x05};

    // Example IP addresses and protocol.
    uint32_t srcIp = 0xC0A80001;  // 192.168.0.1
    uint32_t destIp = 0xC0A80002; // 192.168.0.2
    uint8_t protocol = 0x06;      // TCP protocol

    // Create an IP packet. (IpPacket constructor takes source IP, destination IP, payload size, protocol, and payload)
    IpPacket ipPacket(srcIp, destIp, payload.size(), protocol, payload);

    // Display the generated IP packet details.
    std::cout << "Generated IP Packet:\n";
    ipPacket.printPacketDetails();

    // Get a formatted packet string for PDCP processing.
    // The format is expected to be "Header|Payload" for PDCP.
    std::string formattedPacket = ipPacket.formatPacket();

    /////////////
    // Step 2: Process the packet through the PDCP layer.
    PDCP pdcp("mysecretkey");
    std::string pdcpPacket = pdcp.processPacket(formattedPacket);
    std::cout << "\nProcessed PDCP Packet:\n" << pdcpPacket << std::endl;

    /////////////
    // Step 3: Pass the PDCP packet to the RLC layer.
    // Convert the PDCP packet string to a vector of uint8_t.
    std::vector<uint8_t> pdcpData(pdcpPacket.begin(), pdcpPacket.end());
    
    RLC rlc;
    std::vector<std::vector<uint8_t>> segmentedRlcPackets = rlc.segmentData(pdcpData);

    // Display segmented RLC packets.
    std::cout << "\nSegmented RLC Packets:\n";
    for (size_t i = 0; i < segmentedRlcPackets.size(); ++i) {
        std::cout << "Segment " << i << ": ";
        printData(segmentedRlcPackets[i]);
    }

    // Reassemble the RLC segments back into a single packet.
    std::vector<uint8_t> reassembledData = rlc.reassembleData(segmentedRlcPackets);
    std::cout << "\nReassembled RLC Data: ";
    printData(reassembledData);

    /////////////
    // Step 4: Pass the reassembled data to the MAC layer.
    MAC mac;
    // Prepare transport blocks from the reassembled data.
    std::vector<std::vector<uint8_t>> transportBlocks = mac.prepareTransportBlocks(reassembledData);
    
    // Schedule the transport blocks for transmission.
    std::cout << "\nMAC Layer Scheduling:\n";
    mac.scheduleData(transportBlocks);

    // Optionally, simulate transport block looping or retransmission here if needed.
    // For example, retransmit a specific block if needed:
    // std::vector<uint8_t> retransmittedBlock = rlc.retransmitData(transportBlocks[0], 0);
    // std::cout << "\nRetransmitted Block: ";
    // printData(retransmittedBlock);

    return 0;
}
