#include <iostream>
#include "PDCP/PDCP.h"
// #include "IP/IP.h"      // Uncomment once the IP layer is implemented
// #include "RLC/RLC.h"    // Uncomment once the RLC layer is implemented

int main() {
    // -------------------------------
    // Step 1: Generate a packet from the IP layer
    // TODO: Replace this dummy packet with the actual packet from the IP layer.
    std::string packet = "IPHeaderInformation|This is the payload data that needs processing.";
    
    // -------------------------------
    // Step 2: Process the packet through the PDCP layer
    PDCP pdcp("mysecretkey");
    std::string pdcpPacket = pdcp.processPacket(packet);
    
    // -------------------------------
    // Step 3: Pass the processed packet to the RLC layer
    // TODO: Call the RLC layer to process the PDCP output.
    // Example:
    // RLC rlc;
    // std::string rlcPacket = rlc.processPacket(pdcpPacket);
    
    // For now, output the PDCP processed packet.
    std::cout << "Processed PDCP Packet:\n" << pdcpPacket << std::endl;
    
    return 0;
}
