#include <iostream>
#include "functions.h"

int main() {
    std::cout << "Choose an option:\n";
    std::cout << "1. Hash from input\n";
    std::cout << "2. Hash from file\n";
    std::cout << "3. `konstitucija.txt` test`\n";

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
        default:
            std::cout << "Invalid choice.\n";
    }

    return 0;
}
