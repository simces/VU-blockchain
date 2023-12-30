#ifndef GENERATORS_H
#define GENERATORS_H

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <vector>
#include <bitset>
#include <time.h>
#include <random>
#include <algorithm> 
#include <chrono>
#include <exception>
#include <list>
#include <deque>
#include <map>

#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

using std::string;
using std::cout;
using std::cin;
using std::stoi;
using std::left;
using std::right;
using std::fixed;
using std::setw;
using std::setprecision;
using std::mt19937;
using std::random_device;
using std::uniform_int_distribution;
using std::bernoulli_distribution;
using std::vector;
using std::isspace;
using std::endl;
using std::ifstream;
using std::stringstream;
using std::ofstream;
using std::sort;
using std::runtime_error;
using std::exception;
using std::cerr;
using std::to_string;
using std::count_if;
using std::isdigit;
using std::list;
using std::advance;
using std::deque;
using std::remove_if;
using std::istream;
using std::getline;
using std::bitset;

std::string myHashGen(std::string hashInput);

std::string metroffHashGen(const std::string& input);

std::string miautawnHashGen(std::string input); 

std::string int_to_hex(int input);

std::string vabasouHashGen(const std::string &input);

void getInputFromFile(std::string &input, std::string fileLocation);

void getInputByHand(std::string &input);

std::vector<std::string> stringSplit(std::string input);

void convertToBitStrings(std::vector<std::string> &splits);

std::string mergeBitStrings(std::vector<std::string> &splits);

std::string binaryToHex(std::string input);

std::string vadimasKoHashGen(const std::string &input);

std::string maciukasMHashGen(std::string duomenys);

std::string pauliusUHashGen(const std::string& duomenys);

void add(std::vector<int>& vec, unsigned long long x);

void square(std::vector<int>& vec);

std::string linccerHashGen(const std::string& input);

unsigned int hashDec(int p, int m, std::string s);

std::string hashHex(unsigned int h1, unsigned int h2);

std::string theFeishHashGen(std::string s);\

std::string klaidasKHashGen(const std::string& input);

string jFour404HashGen(string text);

vector<int> hashNo1(string text);

void baseHash (vector<int>& eulerisBi);

vector<int> sequenceGen (unsigned int textSize, int seedSum);

wint_t seedGen (char symbol);

vector <int> bitsGen (unsigned int seed);

void shiftRight (vector<int>& hash, int seq);

vector <int> hashTornado (vector<int> prevHash, vector<int> newHash);

string binaryToHex(vector <int> hashBi);



#endif 
