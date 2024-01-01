#include "functions.h"
#include "generators.h"
#include "md5.h"  
#include "sha1.h"
#include "sha256.h"

#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <chrono>
#include <limits>
#include <random>
#include <vector>
#include <iomanip>
#include <tuple>


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
    std::cout << "1. My hashing algorithm\n";
    std::cout << "2. MD5\n";
    std::cout << "3. SHA1\n";
    std::cout << "4. SHA256\n";
    std::cout << "5. `metroff` hash gen\n";
    std::cout << "6. `miautawn` hash gen\n";
    std::cout << "7. `vabasou` hash gen\n";
    std::cout << "8. `vadimasKo` hash gen\n";
    std::cout << "9. `naciukasM` hash gen\n";
    std::cout << "10. `pauliusU` hash gen\n";
    std::cout << "11. `linccer` hash gen\n";    
    std::cout << "12. `theFeish` hash gen\n";     
    std::cout << "13. `klaidasK` hash gen\n";       
    std::cout << "14. `jFour404` hash gen\n";  
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    return choice;
}


std::string performHashing(const std::string& input, int algorithmChoice) {
    switch (algorithmChoice) {
        case 1: return myHashGen(input);
        case 2: return md5(input);
        case 3: return sha1(input);
        case 4: return sha256(input);
        case 5: return metroffHashGen(input);
        case 6: return miautawnHashGen(input);
        case 7: return vabasouHashGen(input);
        case 8: return vadimasKoHashGen(input);
        case 9: return maciukasMHashGen(input);
        case 10: return pauliusUHashGen(input);
        case 11: return linccerHashGen(input);
        case 12: return theFeishHashGen(input);
        case 13: return klaidasKHashGen(input);
        case 14: return jFour404HashGen(input);
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
    int numRuns = 10; 
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


void generateCollisionFile() {
    std::ofstream outFile("hash_gen/generatedFiles/collision.txt");
    if (!outFile.is_open()) {
        std::cerr << "Unable to open file for writing.\n";
        return;
    }

    const std::vector<int> lengths = {10, 100, 500, 1000};
    const int pairsEach = 25000;  
    const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> dist(0, chars.size() - 1);

    for (int len : lengths) {
        for (int i = 0; i < pairsEach; ++i) {
            std::string str1, str2;
            for (int j = 0; j < len; ++j) {
                str1 += chars[dist(generator)];
                str2 += chars[dist(generator)];
            }
            outFile << str1 << "," << str2 << "\n";
        }
    }
    outFile.close();
}


void collisionTest(int algorithmChoice) {
    std::ifstream inFile("hash_gen/generatedFiles/collision.txt");
    if (!inFile.is_open()) {
        std::cerr << "Unable to open file for reading.\n";
        return;
    }

    std::string line, str1, str2, hashValue;
    int collisions = 0, totalPairs = 0;
    std::vector<std::tuple<std::string, std::string, std::string>> collisionDetails;

    while (std::getline(inFile, line)) {
        std::size_t delimiterPos = line.find(',');
        str1 = line.substr(0, delimiterPos);
        str2 = line.substr(delimiterPos + 1);

        hashValue = performHashing(str1, algorithmChoice);
        if (hashValue == performHashing(str2, algorithmChoice)) {
            collisions++;
            collisionDetails.emplace_back(str1, str2, hashValue);
        }
        totalPairs++;
    }


    for (const auto& collision : collisionDetails) {
        std::string collisionStr1, collisionStr2, collisionHash;
        std::tie(collisionStr1, collisionStr2, collisionHash) = collision;
        std::cout << "Collision pair: " << collisionStr1 << " and " << collisionStr2 << " produce the same hash: " << collisionHash << "\n";
    }
    std::cout << collisions << " collisions found out of " << totalPairs << " pairs.\n";
    inFile.close();
}


void generateAvalancheFile() {
    std::ofstream outFile("hash_gen/generatedFiles/avalanche.txt");
    if (!outFile.is_open()) {
        std::cerr << "Unable to open file for writing.\n";
        return;
    }

    const std::vector<int> lengths = {10, 100, 500, 1000};
    const int pairsEach = 25000;
    const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> dist(0, chars.size() - 1);
    std::uniform_int_distribution<> posDist(0, chars.size() - 2);

    for (int len : lengths) {
        for (int i = 0; i < pairsEach; ++i) {
            std::string str1, str2;
            for (int j = 0; j < len; ++j) {
                str1 += chars[dist(generator)];
            }

            str2 = str1;
            int posToChange = rd() % len;
            char newChar = chars[posDist(generator)];
            while (newChar == str2[posToChange]) { 
                newChar = chars[posDist(generator)];
            }
            str2[posToChange] = newChar;

            outFile << str1 << "," << str2 << "\n";
        }
    }
    outFile.close();
}


std::string transformToBinary(char hexChar) {
    switch (hexChar) {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'a': case 'A': return "1010";
        case 'b': case 'B': return "1011";
        case 'c': case 'C': return "1100";
        case 'd': case 'D': return "1101";
        case 'e': case 'E': return "1110";
        case 'f': case 'F': return "1111";
        default: return "0000"; 
    }
}


void avalancheTest(int algorithmChoice) {
    std::ifstream inFile("hash_gen/generatedFiles/avalanche.txt");
    if (!inFile.is_open()) {
        std::cerr << "Unable to open file for reading.\n";
        return;
    }

    double bitsMin = 256, bitsMax = 0, bitsAvg = 0;
    double hexMin = 64, hexMax = 0, hexAvg = 0;
    int totalPairs = 0;

    std::string line, baseStr, variantStr;

    while (std::getline(inFile, line)) {
        std::size_t delimiterPos = line.find(',');
        baseStr = line.substr(0, delimiterPos);
        variantStr = line.substr(delimiterPos + 1);

        std::string hashBase = performHashing(baseStr, algorithmChoice);
        std::string hashVariant = performHashing(variantStr, algorithmChoice);

        double diffHex = 0, diffBits = 0;
        for (size_t i = 0; i < hashBase.length(); ++i) {
            if (hashBase[i] != hashVariant[i]) diffHex++;
            
            std::string binaryBase = transformToBinary(hashBase[i]);
            std::string binaryVariant = transformToBinary(hashVariant[i]);
            for (size_t j = 0; j < binaryBase.size(); ++j) {
                if (binaryBase[j] != binaryVariant[j]) diffBits++;
            }
        }

        hexMin = std::min(hexMin, diffHex);
        hexMax = std::max(hexMax, diffHex);
        hexAvg += diffHex;

        bitsMin = std::min(bitsMin, diffBits);
        bitsMax = std::max(bitsMax, diffBits);
        bitsAvg += diffBits;

        totalPairs++;
    }

    hexAvg = hexAvg / 64 / totalPairs * 100;
    bitsAvg = bitsAvg / 256 / totalPairs * 100;

    std::cout << "                               Hex     Bits\n";
    std::cout << "Minimum difference in pairs:   " << hexMin << "      " << bitsMin << "\n";
    std::cout << "Maximum difference in pairs:   " << hexMax << "      " << bitsMax << "\n";
    std::cout << "Average difference in pairs:   " << std::setprecision(3) << hexAvg << "%   " << std::setprecision(3) << bitsAvg << "%\n";

    inFile.close();
}