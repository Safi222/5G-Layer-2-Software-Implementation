#include "PDCP.h"
#include <sstream>
#include <iostream>
#include <functional> // For std::hash

// Constructor: Store the provided encryption key.
PDCP::PDCP(const std::string& encryptionKey) : key(encryptionKey) {}

// Function: compressHeader
// Purpose: Simulate header compression by removing vowels (as an example of data reduction).
std::string PDCP::compressHeader(const std::string& header) {
    std::string compressed;
    for (char c : header) {
        // Remove vowels to simulate compression.
        if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' &&
            c != 'A' && c != 'E' && c != 'I' && c != 'O' && c != 'U') {
            compressed.push_back(c);
        }
    }
    return compressed;
}

// Function: encryptData
// Purpose: Simulate encryption using XOR encryption.
// Explanation: Each byte of the data is XORed with a byte from the key (repeated as needed).
std::string PDCP::encryptData(const std::string& data) {
    std::string encrypted = data;
    size_t keyLength = key.length();
    for (size_t i = 0; i < data.length(); ++i) {
        encrypted[i] = data[i] ^ key[i % keyLength];
    }
    return encrypted;
}

// Function: computeIntegrity
// Purpose: Simulate an integrity check using a basic hash function.
// Explanation: This function computes a hash value (as a string) to simulate integrity protection.
std::string PDCP::computeIntegrity(const std::string& data) {
    std::hash<std::string> hash_fn;
    size_t hash = hash_fn(data);
    std::ostringstream oss;
    oss << hash;
    return oss.str();
}

// Function: processPacket
// Purpose: Process a complete packet through the PDCP layer by compressing the header,
// encrypting the payload, and computing an integrity check.
// Expected format of the input packet: "Header|Payload"
std::string PDCP::processPacket(const std::string& packet) {
    // Find the delimiter between header and payload.
    size_t delimiterPos = packet.find('|');
    if (delimiterPos == std::string::npos) {
        std::cerr << "Invalid packet format. Expected header and payload separated by '|'" << std::endl;
        return "";
    }
    // Split the packet into header and payload.
    std::string header = packet.substr(0, delimiterPos);
    std::string payload = packet.substr(delimiterPos + 1);

    // Step 1: Compress the header.
    std::string compressedHeader = compressHeader(header);

    // Step 2: Encrypt the payload.
    std::string encryptedPayload = encryptData(payload);

    // Step 3: Compute the integrity of the encrypted payload.
    std::string integrityCheck = computeIntegrity(encryptedPayload);

    // Combine all parts into a final PDCP packet format:
    // Format: compressedHeader | encryptedPayload | integrityCheck
    std::string processedPacket = compressedHeader + "|" + encryptedPayload + "|" + integrityCheck;
    return processedPacket;
}
