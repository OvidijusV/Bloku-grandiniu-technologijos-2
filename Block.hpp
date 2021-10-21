#ifndef BLOCK_H
#define BLOCK_H

#include "declarations.h"
#include "Transaction.hpp"
class Block{
    private:
    string prevHash;
    string timestamp;
    double version;
    string merkleHash;
    int nonce;
    int difficulty;
    vector<Transaction> transactions;

    public:
    Block(string prev_block_hash, int difficulty_target, double version);
    string setMerkleHash();
    //void add_transactions(vector<Transaction>&);
    void addTransaction(Transaction&);
    void mine();
    string getHash();
    vector<Transaction> get_transactions();
    void output();
    int getTransactionCount();
    int getDifficulty();
    string get_timestamp();
    int getTransactionVolume();

};

Block::Block(string prevHash, int difficulty, double version) : 
    prevHash{prevHash}, difficulty{difficulty}, version{version} {
    nonce = 1;
    timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();;
}

void Block::addTransaction(Transaction transaction){
    transactions.push_back(transaction);
};

void Block::setMerkleHash(){
    string hashMerkle;
    for(int i=0; i<transactions.size(); i++){
        hashMerkle += transactions[i].transactionID;
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

int Block::getTransactionCount() {
    return transactions.size();
};

int Block::getDifficulty(){
    return difficulty;
};

int Block::getTransactionVolume(){
    int output = 0;
    for(Transaction& t: transactions) {
        output += t.get_amount();
    }
    return output;
};

vector<Transaction> Block::get_transactions() {
    return transactions;
};

string Block::get_timestamp() {
    return timestamp;
};

void Block::output() {
    cout << "Block hash: " << getHash() << endl
    << "Previous block hash: " << prevHash << endl
    << "Timestamp: " << get_timestamp() << endl
    << "Transaction number: " << getTransactionCount() << endl
    << "Difficulty: " << difficulty << endl
    << "Merkle root hash: " << setMerkleHash() << endl
    << "Version: " << version << endl
    << "Nonce: " << nonce << endl
    << "Transactions volume: " << getTransactionVolume() << endl << endl
    << "Transactions" << endl
    << string(50, '-') << endl;
    for(Transaction &t: transactions) {
        cout << t.to_sstream().rdbuf();
    }
}

#endif