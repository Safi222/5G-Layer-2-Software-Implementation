#include <iostream>
#include "PDCP/PDCP.h"
#include "RLC/RLC.h"
// #include "IP/IP.h"      // Uncomment once the IP layer is implemented

void printData(const std::vector<uint8_t>& data) {
    for (size_t i = 0; i < data.size(); i++) {
        printf("%02x ", data[i]);
    }
    printf("\n");
}

int main() {
    // -------------------------------
    // Step 1: Generate a packet from the IP layer
    // For now, we're using a dummy packet to simulate the IP layer's output
    std::string packet = "IPHeaderInformation|This is the payload data that needs processing.";
    
    // -------------------------------
    // Step 2: Process the packet through the PDCP layer
    PDCP pdcp("mysecretkey");
    std::string pdcpPacket = pdcp.processPacket(packet);
    
    // -------------------------------
    // Step 3: Pass the processed packet to the RLC layer
    RLC rlc;
    std::vector<std::vector<uint8_t>> segmentedRlcPackets = rlc.segmentData({pdcpPacket.begin(), pdcpPacket.end()});

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