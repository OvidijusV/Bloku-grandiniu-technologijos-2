#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "declarations.h"
#include "Block.hpp"

class Blockchain{
    private:
    vector<Block> blocks;

    public:
    void addBlock(Block&);
    int blockCount();
    string getPrevBlockHash();
    int getTransactionCount();
    void outputBlock();

};

void Blockchain::addBlock(Block& block) {
    blocks.push_back(block);
};

int Blockchain::blockCount() {
    return blocks.size();
}

int Blockchain::getTransactionCount() {
    int output = 0;
    for(Block &b: blocks) {
        output += b.getTransactionCount();
    }
    return output;
};

void Blockchain::outputBlock() {
    cout << endl << string(50, '-') << endl << "***Blockchain***" << endl
    << "Blocks number: " << blockCount() << endl
    << "Transactions number: " << getTransactionCount() << endl;
}

#endif