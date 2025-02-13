#include "PDCP.h"
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <functional> // For std::hash

// Constructor: Store the provided encryption key.
PDCP::PDCP(const std::string& encryptionKey) : key(encryptionKey) {}

// Function: compressHeader (Simulate header compression)
std::string PDCP::compressHeader(const std::string& header) {
    // A simple example of header compression: 
    std::string compressed = header;

    // For example, remove the version if it's fixed to 'IPv4'
    size_t pos = compressed.find("IPv4");
    if (pos != std::string::npos) {
        compressed.erase(pos, 4); // Remove 'IPv4'
    }

    // Return the compressed header
    return compressed;
}


// AES Encryption function using EVP (AES-128-CBC)
std::string PDCP::encryptData(const std::string& data) {
    // EVP Cipher context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (ctx == nullptr) {
        std::cerr << "Error initializing EVP context" << std::endl;
        return "";
    }

    // Generate a random IV
    unsigned char iv[AES_BLOCK_SIZE];
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        std::cerr << "Error generating IV" << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }

    // Create a buffer for the encrypted data
    std::vector<unsigned char> encryptedData(data.size() + AES_BLOCK_SIZE);

    // Initialize encryption with AES-128-CBC
    if (EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr,
                           reinterpret_cast<const unsigned char*>(key.c_str()), iv) != 1) {
        std::cerr << "Error initializing AES encryption" << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }

    // Encrypt the data
    int len = 0;
    int cipherLen = 0;
    if (EVP_EncryptUpdate(ctx, encryptedData.data(), &len,
                          reinterpret_cast<const unsigned char*>(data.c_str()), data.size()) != 1) {
        std::cerr << "Error during AES encryption" << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }
    cipherLen = len;

    // Finalize encryption
    if (EVP_EncryptFinal_ex(ctx, encryptedData.data() + len, &len) != 1) {
        std::cerr << "Error finalizing AES encryption" << std::endl;
        EVP_CIPHER_CTX_free(ctx);
        return "";
    }
    cipherLen += len;

    // Clean up
    EVP_CIPHER_CTX_free(ctx);

    return std::string(encryptedData.begin(), encryptedData.begin() + cipherLen);
}

// Function to compute integrity check using SHA-256
std::string PDCP::computeIntegrity(const std::string& data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256_ctx;

    SHA256_Init(&sha256_ctx);
    SHA256_Update(&sha256_ctx, data.c_str(), data.size());
    SHA256_Final(hash, &sha256_ctx);

    std::ostringstream oss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        oss << std::hex << (int)hash[i];
    }
    return oss.str();
}

// Function: processPacket
// Process a packet by compressing the header, encrypting the payload, and computing integrity.
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

    // Step 1: Compress the header (simulated).
    std::string compressedHeader = compressHeader(header);

    // Step 2: Encrypt the payload using AES.
    std::string encryptedPayload = encryptData(payload);

    // Step 3: Compute the integrity of the encrypted payload using SHA-256.
    std::string integrityCheck = computeIntegrity(encryptedPayload);

    // Combine all parts into a final PDCP packet format:
    // Format: compressedHeader | encryptedPayload | integrityCheck
    std::string processedPacket = compressedHeader + "|" + encryptedPayload + "|" + integrityCheck;
    return processedPacket;
}
