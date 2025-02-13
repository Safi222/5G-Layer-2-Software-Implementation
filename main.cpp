#include <iostream>
#include "PDCP/PDCP.h"
#include "RLC/RLC.h"
#include "IpPacketGenerator/IpPacketGenerator.h"

void printData(const std::vector<uint8_t>& data) {
    for (size_t i = 0; i < data.size(); i++) {
        printf("%02x ", data[i]);
    }
    printf("\n");
}

int main() {
    // -------------------------------
    // Step 1: Generate a packet from the IP layer
    // Define some example data (payload)
    std::vector<uint8_t> data = {0x01, 0x02, 0x03, 0x04, 0x05};  // Example payload data

    // Define source and destination IPs (in this case, using integers to represent IP addresses)
    uint32_t srcIp = 0xC0A80001;  // Example source IP (192.168.0.1)
    uint32_t destIp = 0xC0A80002; // Example destination IP (192.168.0.2)

    // Define protocol (e.g., 0x06 for TCP)
    uint8_t protocol = 0x06; // TCP protocol

    // Create an IpPacket instance with the defined values
    IpPacket ipPacket(srcIp, destIp, data.size(), protocol, data);

    // Print the packet details
    std::cout << "Generated IP Packet: \n";
    ipPacket.printPacketDetails();  // This will display the IP header and payload info

    // Generate the formatted packet to pass to PDCP
    std::string formattedPacket = ipPacket.formatPacket();

    // -------------------------------
    // Step 2: Process the packet through the PDCP layer
    PDCP pdcp("mysecretkey");
    std::string pdcpPacket = pdcp.processPacket(formattedPacket);
    
    // -------------------------------
    // Step 3: Pass the processed packet to the RLC layer
    RLC rlc;
    // Convert the processed PDCP packet (a std::string) to a std::vector<uint8_t>
    std::vector<uint8_t> pdcpData(pdcpPacket.begin(), pdcpPacket.end());
    std::vector<std::vector<uint8_t>> segmentedRlcPackets = rlc.segmentData(pdcpData);

    // -------------------------------
    // Step 4: Display the segmented RLC packets
    std::cout << "Processed PDCP Packet:\n" << pdcpPacket << std::endl;
    std::cout << "Segmented RLC Packets: \n";
    for (size_t i = 0; i < segmentedRlcPackets.size(); ++i) {
        std::cout << "Segment " << i << ": ";
        printData(segmentedRlcPackets[i]);
    }

    // -------------------------------
    // Step 5: Reassemble the RLC packets back into a single packet
    std::vector<uint8_t> reassembledData = rlc.reassembleData(segmentedRlcPackets);
    std::cout << "Reassembled RLC Data: ";
    printData(reassembledData);

    // -------------------------------
    // Step 6: Simulate retransmission of a segment (e.g., segment 1)
    std::vector<uint8_t> retransmittedSegment = rlc.retransmitData(segmentedRlcPackets[1], 0);
    std::cout << "Retransmitted Segment: ";
    printData(retransmittedSegment);

    return 0;
}