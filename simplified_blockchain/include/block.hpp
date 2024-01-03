#ifndef BLOCK_H
#define BLOCK_H

#include "declarations.h"
#include "transaction.hpp"
#include "user.hpp"
#include "merkle.hpp"


class Block {

    private:
    int index;
    int nonce;
    string timestamp;
    string curHash;
    string curData;
    string genHash() const;

    public:
    int version = 1;
    unsigned int difficulty;
    vector<Transaction> transactions;
    string merkleHash;
    string prevHash;
    
    Block(int nIndexIn, vector<Transaction> transactions);
    void mine(unsigned int difficulty);
    string getPrevHash();
    string setMerkleHash();
    string getHash();
    string getTimestamp();
    int getDifficulty();
    int getTransactionCount();
    int getTransactionVolume();
    int getVersion();
    int getNonce();
};


Block::Block(int IndexIn, vector<Transaction> transactions) {
    index = IndexIn;
    this -> transactions = transactions;
    nonce = -1;

    std::time_t now = std::time(nullptr);
    char buf[80];
    std::strftime(buf, sizeof(buf), "%b %d, %Y, %I:%M:%S %p", std::localtime(&now));
    timestamp = buf;
}


string Block::getPrevHash() {
    return this -> prevHash;
}


string Block::getHash() {
    return curHash;
}


string Block::setMerkleHash() {
    std::vector<std::string> transactionHashes;
    for (const auto& transaction : transactions) {
        transactionHashes.push_back(transaction.transactionId); // Assuming transactionId is already a hash
    }

    MerkleTree merkleTree(transactionHashes);
    return merkleTree.getMerkleRoot();
}


void Block::mine(unsigned int difficulty) {
    char* cstr;
    cstr = new char[difficulty + 1];

    for (int i = 0; i < difficulty; i++) {
        cstr[i] = '0';
    }

    cstr[difficulty] = '\0';
    
    string str(cstr);

    merkleHash = setMerkleHash();

    while(curHash.substr(0, difficulty) !=str){
        nonce++;
        curHash = genHash();
    }
    cout << "Hash of block " << index << ": " << curHash << "\n";
};


string Block::genHash() const{
    stringstream ss;
    ss << index << timestamp << curData << nonce << prevHash;
    return hashFunction(ss.str());
};


int Block::getDifficulty() {
    return this -> difficulty;
};


int Block::getVersion() {
    return this -> version;
};


int Block::getNonce() {
    return this -> nonce;
};


string Block::getTimestamp() {
    return timestamp;
};


int Block::getTransactionCount() {
    return transactions.size();
}


int Block::getTransactionVolume() {
    int output = 0;
    for(Transaction& t: transactions) {
        output += t.amount;
    }
    return output;
}


#endif