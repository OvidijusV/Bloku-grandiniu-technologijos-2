#include "Block.hpp"
#include "Blockchain.hpp"
#include "declarations.h"
#include "Transaction.hpp"
#include "User.hpp"

int main(){
    srand(time(0));
    vector<User> Users;
    vector<Transaction> transactionPool;
    for(int i=0; i<1000; i++){
        string name = "member" + to_string(i+1);
        int balance = 100 + (rand() % 1000000);
        string publicKey;
        for(int i=0; i < 3 + (rand() % 20); i++){
            publicKey += char(29 + (rand() % 119));
        }
        publicKey = hashFunction(publicKey);
        User newMember(name, publicKey, balance);
        Users.push_back(newMember);
    }
    
    for(int i=0; i<10000; i++){
        int ranSender = rand() % 1000;
        int ranReceiver = rand() % 1000;
        while(ranSender == ranReceiver){
            ranSender = rand() % 1000;
            ranReceiver = rand() % 1000;
        }
        User* sender = &Users[ranSender];
        User* receiver = &Users[ranReceiver];
        Transaction newTransaction(sender, receiver, rand() % sender->getBalance());
        transactionPool.push_back(newTransaction);
    }

    vector<Transaction> transactionToBlock;
    int numOfTransactions = 10000;
    addTransactionsToBlock(transactionToBlock, transactionPool, numOfTransactions);
    Block mainBlock(0, transactionToBlock);
    Blockchain blockChain(mainBlock);
    int g = 1;
    while(transactionPool.size()>=100){
        transactionToBlock.clear();
        addTransactionsToBlock(transactionToBlock, transactionPool, numOfTransactions);
        cout << "Mining block " << g << "\n";
        blockChain.addBlock(Block(g, transactionToBlock));
        g++;
    }

    transactionToBlock.clear();
}