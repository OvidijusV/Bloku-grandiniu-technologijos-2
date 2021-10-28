#ifndef BLOCK_H
#define BLOCK_H

#include "declarations.h"
#include "Transaction.hpp"
#include "User.hpp"
class Block{
    private:
    string timestamp;
    double version = 0.1;
    int index;
    string merkleHash;
    int nonce;
    unsigned int difficulty;
    vector<Transaction> transactions;

    public:
    string prevHash;
    Block(int nIndexIn, vector<Transaction> transactions);
    string curHash;
    string setMerkleHash();
    string genHash();
    void mine(unsigned int difficulty);
    string getPrevHash();
    string getHash();
    int getDifficulty();
    string get_timestamp();
    int getTransactionCount();
    int getTransactionVolume();
    double getVersion();
    int getNonce();

};

Block::Block(int IndexIn, vector<Transaction> transactions){
    index = IndexIn;
    this->transactions = transactions;
    nonce = -1;
    this->timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

string Block::getPrevHash(){
    return this->prevHash;
}

string Block::getHash(){
    return curHash;
}

string Block::setMerkleHash(){
    string hashMerkle;
    for(int i=0; i<transactions.size(); i++){
        hashMerkle += transactions[i].transactionId;
    }
    //merkleHash = hashFunction(hashMerkle);
    return hashFunction(hashMerkle);
};

void Block::mine(unsigned int difficulty) {
    char* cstr;
    cstr = new char[difficulty+1];
    for(int i=0; i<difficulty; i++){
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

string Block::genHash() {
    stringstream ss;
    ss << index << timestamp << version << nonce << prevHash;
    return hashFunction(ss.str());
};


int Block::getDifficulty(){
    return this->difficulty;
};

double Block::getVersion(){
    return this->version;
};

int Block::getNonce(){
    return this->nonce;
};

string Block::get_timestamp() {
    return this->timestamp;
};

int Block::getTransactionCount() {
    return transactions.size();
}

int Block::getTransactionVolume(){
    int output = 0;
    for(Transaction& t: transactions) {
        output += t.amount;
    }
    return output;
}


#endif