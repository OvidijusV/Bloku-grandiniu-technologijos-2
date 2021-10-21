#ifndef USER_H
#define USER_H

#include "declarations.h"

class User {
    public:
    string publicKey;
    User(string name, string publicKey, int balance);
    string getKey();

    private:
    string name;
    int balance;

    string getName();
    int getBalance();
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

#endif