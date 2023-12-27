#include "functions.h"
#include <string>
#include <cmath>

std::string hashing(std::string hashInput) {

    // salt'as
    const std::string salt = "nKd_n3aTsP3siT";
    hashInput += salt;

    const unsigned long long prime1 = 709607;
    const unsigned long long prime2 = 295099;
    unsigned long long hash = prime1;

    for (char c : hashInput) {
        hash ^= (hash << 5) + (hash >> 2) + static_cast<unsigned int>(c);
    }

    hash += prime2 * hashInput.length();

    std::string hashOutput;
    const std::string hex = "0123456789abcdef";

    // hash generavimas (64 chars)
    for (int i = 0; i < 64; i++) {
        hash = (hash * prime1) ^ (hash >> 3);
        hashOutput += hex[hash % 16];
    }

    return hashOutput;
}

