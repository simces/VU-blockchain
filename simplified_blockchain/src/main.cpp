#include "block.hpp"
#include "blockchain.hpp"
#include "declarations.h"
#include "transaction.hpp"
#include "user.hpp"

void addTransactionsToBlock(vector<Transaction> &transactionToBlock, vector<Transaction> &transactionPool, int &numOfTransactions){

    for(int i = 0; i < 100; i++) {
        int transactionIndex = rand() % numOfTransactions;
        int transactionAmount = transactionPool[transactionIndex].amount;
        transactionPool[transactionIndex].sender -> setBalance(transactionPool[transactionIndex].sender -> getBalance() - transactionAmount);
        transactionPool[transactionIndex].receiver -> setBalance(transactionPool[transactionIndex].receiver -> getBalance() + transactionAmount);
        transactionToBlock.push_back(transactionPool[transactionIndex]);
        // cout << "Sender key: " << transactionPool[transactionIndex].senderKey << " Receiver key: " << transactionPool[transactionIndex].receiverKey << " Amount: " << transactionPool[transactionIndex].amount << "\n";
        transactionPool.erase(transactionPool.begin()+(transactionIndex));
        numOfTransactions--;
    }
}


int main(){
    
    srand(time(0));

    vector<User> Users;
    ofstream users("simplified_blockchain/output/users.txt");

    for (int i = 0; i < 1000; i++) {
        string name = "member" + to_string(i+1);
        int balance = 100 + (rand() % 1000000);

        string publicKey;

        for (int i=0; i < 3 + (rand() % 20); i++) {
            publicKey += char(29 + (rand() % 119)); }
        
        publicKey = hashFunction(publicKey);
        User newMember(name, publicKey, balance);
        users << "Name: " << name << endl << "Public key: " << publicKey << endl << "Balance: " << balance << endl 
              << "----------------------------------------------------------------------" << endl;
        Users.push_back(newMember);
    }

    users.close();


    int numOfTransactions = 10000;
    vector<Transaction> transactionPool;
    ofstream transactions("simplified_blockchain/output/transactions.txt");

    for (int i = 0; i < numOfTransactions; i++) {
        int ranSender = rand() % 1000;
        int ranReceiver = rand() % 1000;

        while (ranSender == ranReceiver) {
            ranSender = rand() % 1000;
            ranReceiver = rand() % 1000;
        }

        User* sender = &Users[ranSender];
        User* receiver = &Users[ranReceiver];

        int transactionAmount = rand() % sender -> getBalance();
        Transaction newTransaction(sender, receiver, transactionAmount);

        if (newTransaction.transactionId == hashFunction(sender -> getKey() + receiver -> getKey() + std::to_string(transactionAmount))) {
        transactionPool.push_back(newTransaction);
        transactions << "Transaction ID: " << newTransaction.transactionId << endl
                     << "Sender public key: " << sender->getKey() << endl
                     << "Receiver public key: " << receiver->getKey() << endl
                     << "Transaction amount: " << transactionAmount << endl
                     << "----------------------------------------------------------------------" << endl;
    } else {
        cout << "Couldn't verify the transaction";
    }
}


    vector<Transaction> transactionToBlock;
    addTransactionsToBlock(transactionToBlock, transactionPool, numOfTransactions);

    ofstream blocks("simplified_blockchain/output/blocks.txt");
    ofstream remainingTransactions("simplified_blockchain/output/remainingTransactions.txt");

    Block mainBlock(0, transactionToBlock);
    Blockchain blockChain(mainBlock);

    int blockNr = 1;

    while (transactionPool.size() >= 100){
        transactionToBlock.clear();
        addTransactionsToBlock(transactionToBlock, transactionPool, numOfTransactions);
        cout << "Mining block " << blockNr << "\n";
        blockChain.addBlock(Block(blockNr, transactionToBlock));
        
        blocks  << "\nBlock number: " << blockNr << endl  
                << "Block hash: " << blockChain.getLastBlock().getHash() << endl
                << "Previous block hash: " << blockChain.getLastBlock().getPrevHash() << endl
                << "Mined on: " << blockChain.getLastBlock().getTimestamp() << endl
                << "Difficulty: " << blockChain.getLastBlock().getDifficulty() << endl
                << "Merkle root hash: " << blockChain.getLastBlock().setMerkleHash() << endl
                << "Version: " << blockChain.getLastBlock().getVersion() << endl
                << "Nonce: " << blockChain.getLastBlock().getNonce() << endl
                << "Transaction number: " << blockChain.getLastBlock().getTransactionCount() << endl
                << "Transactions volume: " << blockChain.getLastBlock().getTransactionVolume() << endl << endl
                << "Transactions" << endl << string(50, '-') << endl;

        for(Transaction &t: transactionToBlock) {
        blocks  << "Transaction ID: " << t.transactionId << endl << "Sender public key: " << t.sender -> getKey() << endl 
                << "Receiver public key: " << t.receiver -> getKey() << endl << "Transaction amount: " << t.amount << endl 
                << "----------------------------------------------------------------------" << endl; }
        blockNr++;
    }

    // test to see if the pool clears correctly
    // for (const auto& transaction : transactionPool) {
    // remainingTransactions << "Transaction ID: " << transaction.transactionId << endl;
    // remainingTransactions << "Sender public key: " << transaction.sender -> getKey() << endl;
    // remainingTransactions << "Receiver public key: " << transaction.receiver -> getKey() << endl;
    // remainingTransactions << "Transaction amount: " << transaction.amount << endl;
    // remainingTransactions << "----------------------------------------------------------------------" << endl;
    // }

    blocks.close();
    transactionToBlock.clear();
}