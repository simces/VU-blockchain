#include <iostream>
#include "functions.h"

int main() {
    std::string input;
    std::cout << "Enter a string to hash: ";
    std::getline(std::cin, input);

    std::string hashedValue = hashing(input);
    std::cout << "Hashed Value: " << hashedValue << std::endl;

    return 0;
}
