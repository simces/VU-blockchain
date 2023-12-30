#include <iostream>
#include "functions.h"

int main() {
    std::cout << "Choose an option:\n";
    std::cout << "1. Hash from input\n";
    std::cout << "2. Hash from file\n";
    std::cout << "3. Hash efficiency test (konstitucija.txt)`\n";
    std::cout << "4. Collision test\n";
    std::cout << "5. Avalanche test\n";

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            hashFromInput();
            break;
        case 2:
            hashFromFile();
            break;
        case 3:
            konstitucijaTest();
            break;
        case 4: {
            generateCollisionFile(); // it'll generate a file with 1 000 000 pairs, change number before building the file
            int algorithmChoice = chooseHashingAlgorithm();
            collisionTest(algorithmChoice);
            break;
        }
        case 5: {
            // generateAvalancheFile();
            int algorithmChoice = chooseHashingAlgorithm();
            avalancheTest(algorithmChoice);
            break;
        }
        default:
            std::cout << "Invalid choice.\n";
    }

    return 0;
}
