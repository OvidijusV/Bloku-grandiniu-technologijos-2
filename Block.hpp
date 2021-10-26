#ifndef BLOCK_H
#define BLOCK_H

#include "declarations.h"
#include "Transaction.hpp"
#include "User.hpp"
class Block{
    private:
    string prevHash;
    string timestamp;
    double version = 0.1;
    int index;
    string merkleHash;
    int nonce;
    int difficulty;
    vector<Transaction> transactions;
    bool check_hash_difficulty(string&);

    public:
    Block(int nIndexIn, vector<Transaction> transactions);
    string setMerkleHash();
    //void add_transactions(vector<Transaction>&);
    void mine();
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

bool Block::check_hash_difficulty(string &hash) {
    for (int i = 0; i < difficulty; i++) {
        if (hash[i] != '0'){
            return false;
        }
    }
    return true;
}

string Block::getPrevHash(){
    return this->prevHash;
}

string Block::setMerkleHash(){
    string hashMerkle;
    for(int i=0; i<transactions.size(); i++){
        hashMerkle += transactions[i].transactionId;
    }
    merkleHash = hashFunction(hashMerkle);
};

void Block::mine() {
    string block_hash = getHash();
    while(!check_hash_difficulty(block_hash)) {
        nonce++;    
        block_hash = getHash();
    }
};

string Block::getHash() {
    stringstream ss;
    ss << prevHash << timestamp << version << setMerkleHash() << nonce << difficulty;
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