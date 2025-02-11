#include "RLC.h"
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>

// Constructor initializes sequence number to 0.
RLC::RLC() : sequenceNumber(0) {}

// Function to segment data into smaller chunks
std::vector<std::vector<uint8_t>> RLC::segmentData(const std::vector<uint8_t>& data) {
    std::vector<std::vector<uint8_t>> segments;
    size_t dataSize = data.size();
    const size_t maxSegmentSize = 128; // Maximum size of RLC PDU

    // Split the data into segments
    for (size_t i = 0; i < dataSize; i += maxSegmentSize) {
        std::vector<uint8_t> segment(data.begin() + i, data.begin() + std::min(i + maxSegmentSize, dataSize));
        segments.push_back(createRlcPdu(segment, sequenceNumber++));
    }

    return segments;
}

// Function to reassemble data from segments
std::vector<uint8_t> RLC::reassembleData(const std::vector<std::vector<uint8_t>>& segments) {
    std::vector<uint8_t> reassembledData;

    // Combine all the segments into one data packet
    for (const auto& segment : segments) {
        reassembledData.insert(reassembledData.end(), segment.begin(), segment.end());
    }

    return reassembledData;
}

// Function to simulate retransmission of a lost segment
std::vector<uint8_t> RLC::retransmitData(const std::vector<uint8_t>& data, int segmentToRetransmit) {
    // For simplicity, return the segment at the given index
    std::vector<uint8_t> retransmittedData;
    retransmittedData.push_back(data[segmentToRetransmit]);
    return retransmittedData;
}

// Helper function to create an RLC PDU (Packet Data Unit)
std::vector<uint8_t> RLC::createRlcPdu(const std::vector<uint8_t>& data, size_t sequenceNumber) {
    std::vector<uint8_t> pdu;
    
    // Simulate RLC header: Add sequence number (2 bytes for simplicity)
    pdu.push_back(sequenceNumber >> 8);  // Most significant byte of sequence number
    pdu.push_back(sequenceNumber & 0xFF);  // Least significant byte of sequence number
    
    // Add the actual data payload
    pdu.insert(pdu.end(), data.begin(), data.end());

    return pdu;
}
