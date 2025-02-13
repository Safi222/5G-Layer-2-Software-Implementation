#ifndef PDCP_H
#define PDCP_H

#include <string>

// PDCP Class: Implements simplified versions of PDCP functionalities
class PDCP {
public:
    // Constructor: Initialize with an encryption key.
    PDCP(const std::string& encryptionKey);

    // Compress the header (simulate header compression)
    std::string compressHeader(const std::string& header);

    // Encrypt data using AES (CBC mode)
    std::string encryptData(const std::string& data);

    // Compute integrity using SHA-256
    std::string computeIntegrity(const std::string& data);

    // Process a packet by applying header compression, encryption, and integrity checking.
    std::string processPacket(const std::string& packet);

private:
    std::string key; // Encryption key for AES encryption.
};

#endif // PDCP_H
