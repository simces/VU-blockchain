#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

std::string customHash(std::string hashInput);

void hashFromInput();

void hashFromFile();

void konstitucijaTest();

int chooseHashingAlgorithm();

std::string performHashing(const std::string& input, int algorithmChoice);

void collisionTest(int algorithmChoice);

void generateCollisionFile();

void generateAvalancheFile();

void avalancheTest(int algorithmChoice);

std::string transformToBinary(char hexChar);

#endif