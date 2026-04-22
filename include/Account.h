#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;

class Account {
private:
    int accNo;
    string name;
    int pin;
    double balance;

public:
    Account();
    Account(int, string, int);

    int getAccNo();
    string getName();
    int getPin();
    double getBalance();

    void deposit(double);
    bool withdraw(double);
};

#endif