#ifndef MAC_H
#define MAC_H

#include <vector>
#include <string>
#include <cstdint>

// MAC Class: Implements basic functions for multiplexing, scheduling, and transport block creation.
class MAC {
public:
    // Constructor
    MAC();

    // Function to simulate receiving data from the RLC layer and preparing transport blocks
    std::vector<std::vector<uint8_t>> prepareTransportBlocks(const std::vector<uint8_t>& data);

    // Function to simulate scheduling and multiplexing of data
    void scheduleData(const std::vector<std::vector<uint8_t>>& transportBlocks);

    // Function to create a MAC header (for simplicity, only includes transport block size)
    std::vector<uint8_t> createMacHeader(size_t blockSize);

private:
    // Helper function to simulate the packaging of data into transport blocks
    std::vector<uint8_t> createTransportBlock(const std::vector<uint8_t>& data);
};

#endif // MAC_H
