#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;

class Account {
private:
    int accNo;
    string name;
    string pin;
    double balance;

    
    int failedAttempts;
    bool isLocked;

public:
    Account();
    Account(int, string, int);
    Account(int, string, string, double);

    int getAccNo();
    string getName();
    string getPin();
    double getBalance();

    void deposit(double);
    bool withdraw(double);

    void incrementFailedAttempts();
    void resetFailedAttempts();
    bool getLockStatus();
    void lockAccount();
    void unlockAccount();
};

#endif