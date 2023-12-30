#include "functions.h"
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include "md5.h"  
#include "sha1.h"
#include "sha256.h"
#include <chrono>
#include <limits>


std::string customHash(std::string hashInput) {

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


void hashFromInput() {
    std::cout << "Enter the string to hash: ";
    std::cin.ignore(); 
    std::string input;
    std::getline(std::cin, input);

    int algorithmChoice = chooseHashingAlgorithm();
    std::string hashedValue = performHashing(input, algorithmChoice);
    std::cout << "Hashed Value: " << hashedValue << std::endl;
}


void hashFromFile() {
    std::string filename;
    int choice;

    std::cout << "Choose a file to hash:\n";
    std::cout << "1. a.txt\n";
    std::cout << "2. b.txt\n";
    std::cout << "3. empty.txt\n";
    std::cout << "4. konstitucija.txt\n";
    std::cout << "5. random_1_1500.txt\n";
    std::cout << "6. random_2_1500.txt\n";
    std::cout << "7. similar_1_1500.txt\n";
    std::cout << "8. similar_2_1500.txt\n";
    std::cout << "Enter your choice: ";

    std::cin >> choice;
    std::cin.ignore();

    switch (choice) {
        case 1: filename = "hash_gen/fileInput/a.txt"; break;
        case 2: filename = "hash_gen/fileInput/b.txt"; break;
        case 3: filename = "hash_gen/fileInput/empty.txt"; break;
        case 4: filename = "hash_gen/fileInput/konstitucija.txt"; break;
        case 5: filename = "hash_gen/fileInput/random_1_1500.txt"; break;
        case 6: filename = "hash_gen/fileInput/random_2_1500.txt"; break;
        case 7: filename = "hash_gen/fileInput/similar_1_1500.txt"; break;
        case 8: filename = "hash_gen/fileInput/similar_2_1500.txt"; break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            return; 
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << '\n';
        return;
    }

    std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    int algorithmChoice = chooseHashingAlgorithm();

    std::string hashedValue = performHashing(fileContent, algorithmChoice);
    std::cout << "Hashed Value: " << hashedValue << std::endl;
}



int chooseHashingAlgorithm() {
    int choice;
    std::cout << "Choose the hashing algorithm:\n";
    std::cout << "1. Custom Hashing Algorithm\n";
    std::cout << "2. MD5\n";
    std::cout << "3. SHA1\n";
    std::cout << "4. SHA256\n";
    std::cout << "Enter your choice (1-4): ";
    std::cin >> choice;
    return choice;
}


std::string performHashing(const std::string& input, int algorithmChoice) {
    switch (algorithmChoice) {
        case 1: return customHash(input);
        case 2: return md5(input);
        case 3: return sha1(input);
        case 4: return sha256(input);
        default: return "Invalid choice";
    }
}


void konstitucijaTest() {
    std::string line, fileContent;
    std::string numLinesStr;

    std::cout << "Enter number of lines to hash (or 'all' for the whole file): ";
    std::cin >> numLinesStr;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

    std::ifstream file("hash_gen/fileInput/konstitucija.txt");
    if (!file.is_open()) {
        std::cerr << "Unable to open konstitucija.txt\n";
        return;
    }

    if (numLinesStr == "all") {
        fileContent.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    } else {
        int numLines = std::stoi(numLinesStr);
        int lineNumber = 0;
        while (lineNumber < numLines && std::getline(file, line)) {
            fileContent += line + "\n";
            lineNumber++;
        }
    }
    file.close();

    int algorithmChoice = chooseHashingAlgorithm();
    int numRuns = 5000; 
    std::chrono::duration<double, std::milli> totalElapsed(0);

    for (int i = 0; i < numRuns; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        std::string hashedValue = performHashing(fileContent, algorithmChoice);
        auto end = std::chrono::high_resolution_clock::now();
        totalElapsed += end - start;
    }

    double averageTime = totalElapsed.count() / numRuns;
    std::cout << "Average time taken to hash: " << averageTime << " ms\n";
}