#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "declarations.h"
#include "Block.hpp"

class Blockchain{
    public:
    Blockchain(Block mainBlock);

    void addBlock(Block blockNew);
    Block getLastBlock() const;

    private:
    unsigned int difficulty;
    vector<Block> blockChain;
    

};

Blockchain::Blockchain(Block mainBlock) {
    blockChain.emplace_back(mainBlock);
    difficulty = 1;
}

Block Blockchain::getLastBlock() const{
    return blockChain.back();
}

void Blockchain::addBlock(Block blockNew) {
    cout << "sw" << endl;
    blockNew.prevHash = getLastBlock().getHash();
    cout << "nesw" << endl;
    blockNew.mine(difficulty);
    cout << "meee" << endl;
    blockChain.push_back(blockNew);
}

#endif