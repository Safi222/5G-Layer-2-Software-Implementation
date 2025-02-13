#include "MAC.h"
#include <iostream>
#include <iterator>

// Constructor: Initialize any parameters or state variables (if needed)
MAC::MAC() {}

// Function to simulate receiving data from the RLC layer and preparing transport blocks
std::vector<std::vector<uint8_t>> MAC::prepareTransportBlocks(const std::vector<uint8_t>& data) {
    std::vector<std::vector<uint8_t>> transportBlocks;

    // Simulate splitting the data into transport blocks (for simplicity, max size is 128 bytes)
    const size_t maxBlockSize = 128;
    size_t dataSize = data.size();
    for (size_t i = 0; i < dataSize; i += maxBlockSize) {
        std::vector<uint8_t> block(data.begin() + i, data.begin() + std::min(i + maxBlockSize, dataSize));
        transportBlocks.push_back(createTransportBlock(block));
    }

    return transportBlocks;
}

// Function to simulate scheduling and multiplexing of data (simple print-out)
void MAC::scheduleData(const std::vector<std::vector<uint8_t>>& transportBlocks) {
    std::cout << "Scheduling " << transportBlocks.size() << " transport blocks for transmission...\n";
    for (size_t i = 0; i < transportBlocks.size(); ++i) {
        std::cout << "Transport Block " << i + 1 << ": ";
        for (auto byte : transportBlocks[i]) {
            printf("%02x ", byte);
        }
        std::cout << std::endl;
    }
}

// Function to create a MAC header
std::vector<uint8_t> MAC::createMacHeader(size_t blockSize) {
    // For simplicity, we simulate a MAC header that contains the block size
    std::vector<uint8_t> header;
    header.push_back(static_cast<uint8_t>(blockSize >> 8));  // MSB of block size
    header.push_back(static_cast<uint8_t>(blockSize & 0xFF)); // LSB of block size
    return header;
}

// Helper function to simulate the packaging of data into transport blocks
std::vector<uint8_t> MAC::createTransportBlock(const std::vector<uint8_t>& data) {
    std::vector<uint8_t> transportBlock;

    // Create a MAC header (this could include more information in a full implementation)
    std::vector<uint8_t> header = createMacHeader(data.size());

    // Add the header to the transport block
    transportBlock.insert(transportBlock.end(), header.begin(), header.end());

    // Add the actual data payload to the transport block
    transportBlock.insert(transportBlock.end(), data.begin(), data.end());

    return transportBlock;
}
