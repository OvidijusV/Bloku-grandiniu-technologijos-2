#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "declarations.h"
#include "User.hpp"

class Transaction {
    public:
    Transaction(User* sender, User* receiver, int amount);
    string transactionId;
    User* sender;
    User* receiver;
    string senderKey;
    string receiverKey;
    int amount;
};

Transaction::Transaction(User* sender, User* receiver, int amount){
    this->sender = sender;
        this->receiver = receiver;
        this->amount = amount;
        this->senderKey = sender->getKey();
        this->receiverKey = receiver->getKey();
        this->transactionId = hashFunction(sender->getKey() + receiver->getKey() + to_string(amount));
}

#endif