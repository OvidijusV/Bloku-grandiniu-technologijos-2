#ifndef USER_H
#define USER_H

#include "declarations.h"

class User {
    public:
    string publicKey;
    User(string name, string publicKey, int balance);

    string getKey();
    void setBalance(int);
    string getName();
    int getBalance();

    private:
    string name;
    int balance;

};

User::User(string name, string publicKey, int balance){
    this->name = name;
    this->publicKey = publicKey;
    this->balance = balance;
}

string User::getKey(){
    return this->publicKey;
}

string User::getName(){
    return this->name;
}

int User::getBalance(){
    return this->balance;
}

void User::setBalance(int value) {
    this->balance = value;
}

#endif