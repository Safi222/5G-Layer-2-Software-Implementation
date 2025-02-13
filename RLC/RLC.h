#ifndef RLC_H
#define RLC_H

#include <vector>
#include <string>
#include <cstdint>

// RLC Class: Implements basic segmentation, reassembly, and retransmission.
class RLC {
public:
    // Constructor
    RLC();

    // Function to segment data into smaller chunks
    std::vector<std::vector<uint8_t>> segmentData(const std::vector<uint8_t>& data);

    // Function to reassemble segmented data back into the original data
    std::vector<uint8_t> reassembleData(const std::vector<std::vector<uint8_t>>& segments);

    // Function to simulate retransmission of lost data
    std::vector<uint8_t> retransmitData(const std::vector<uint8_t>& data, int segmentToRetransmit);

private:
    // Function to simulate RLC PDU construction (data + header)
    std::vector<uint8_t> createRlcPdu(const std::vector<uint8_t>& data, size_t sequenceNumber);

    // Simulate a sequence number tracker for RLC PDU
    size_t sequenceNumber;
};

#endif // RLC_H