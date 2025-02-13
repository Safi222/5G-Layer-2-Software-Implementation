#include <iostream>
#include "PDCP/PDCP.h"
#include "RLC/RLC.h"
#include "MAC/MAC.h"

void printData(const std::vector<uint8_t>& data) {
    for (size_t i = 0; i < data.size(); i++) {
        printf("%02x ", data[i]);
    }
    printf("\n");
}

int main() {
    // Example packet
    std::string packet = "IPHeaderInformation|This is the payload data that needs processing.";

    // Step 1: Process the packet through the PDCP layer
    PDCP pdcp("mysecretkey");
    std::string pdcpPacket = pdcp.processPacket(packet);

    // Step 2: Pass the processed packet to the RLC layer
    RLC rlc;
    std::vector<std::vector<uint8_t>> segmentedRlcPackets = rlc.segmentData({pdcpPacket.begin(), pdcpPacket.end()});

    // Step 3: Pass the RLC packet to the MAC layer
    MAC mac;
    for (auto& rlcPacket : segmentedRlcPackets) {
        mac.scheduleData(mac.prepareTransportBlocks(rlcPacket));
    }

    return 0;
}
