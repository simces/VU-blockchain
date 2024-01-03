#ifndef USER_H
#define USER_H

#include "declarations.h"

class User {

    private:
    string name;
    int balance;

    public:
    User(string name, string publicKey, int balance);
    string publicKey;
    string getKey();
    string getName();
    int getBalance();
    void setBalance(int);
};


User::User(string name, string publicKey, int balance) {
    this -> name = name;
    this -> publicKey = publicKey;
    this -> balance = balance;
}


string User::getKey() {
    return this -> publicKey;
}


string User::getName() {
    return this -> name;
}


int User::getBalance() {
    return this -> balance;
}


void User::setBalance(int value) {
    this -> balance = value;
}

#endif