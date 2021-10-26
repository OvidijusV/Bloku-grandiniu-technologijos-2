#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "declarations.h"
#include "Block.hpp"

class Blockchain{
    public:
    Blockchain(Block mainBlock);

    void addBlock(Block blockNew);

    private:
    int difficulty;
    vector<Block> blockChain;
    Block getLastBlock() const;

};

Blockchain::Blockchain(Block genesisBlock) {
    blockChain.emplace_back(genesisBlock);
    difficulty = 1;
}

Block Blockchain::getLastBlock() const{
    return blockChain.back();
}

void Blockchain::addBlock(Block blockNew) {
    blockNew.getPrevHash() = getLastBlock().getHash();
    blockNew.mine();
    blockChain.push_back(blockNew);
}

#endif