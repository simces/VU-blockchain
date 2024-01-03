#include "declarations.h"

class MerkleTree {
public:
    MerkleTree(const std::vector<std::string>& transactionHashes) {
        buildTree(transactionHashes);
    }

    std::string getMerkleRoot() const {
        return !nodes.empty() ? nodes.back() : "";
    }

private:
    std::vector<std::string> nodes;

    void buildTree(const std::vector<std::string>& transactionHashes) {
        std::vector<std::string> currentLevel = transactionHashes;
        
        while (currentLevel.size() > 1) {
            if (currentLevel.size() % 2 != 0) { // Duplicate last element if odd number of elements
                currentLevel.push_back(currentLevel.back());
            }

            std::vector<std::string> nextLevel;
            for (size_t i = 0; i < currentLevel.size(); i += 2) {
                nextLevel.push_back(hashFunction(currentLevel[i] + currentLevel[i + 1])); 
            }
            currentLevel = nextLevel;
            nodes.insert(nodes.end(), nextLevel.begin(), nextLevel.end()); // Add level to nodes
        }

        if (!currentLevel.empty()) {
            nodes.push_back(currentLevel[0]); // Merkle root
        }
    }
};
