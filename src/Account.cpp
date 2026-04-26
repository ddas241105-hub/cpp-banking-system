#include "../include/Account.h"
#include <iostream>
#include <string>
using namespace std;

// encryption function
string encryptPIN(int pin) {
    int hashed = pin * 31 + 7;
    return to_string(hashed);
}

Account::Account() {}

Account::Account(int accNo, string name, int pin) {
    this->accNo = accNo;
    this->name = name;
    this->pin = encryptPIN(pin);  
    this->balance = 0;
    this->failedAttempts = 0;
    this->isLocked = false;
}


Account::Account(int accNo, string name, string pin, double balance) {
    this->accNo = accNo;
    this->name = name;
    this->pin = pin;
    this->balance = balance;
    this->failedAttempts = 0;
    this->isLocked = false;
}

int Account::getAccNo() { return accNo; }
string Account::getName() { return name; }
string Account::getPin() { return pin; }
double Account::getBalance() { return balance; }

void Account::deposit(double amt) {
    balance += amt;
}

bool Account::withdraw(double amt) {
    if (amt > balance) return false;
    balance -= amt;
    return true;
}

void Account::incrementFailedAttempts() {
    failedAttempts++;
    if (failedAttempts >= 3) {
        isLocked = true;
        cout << "Account locked due to multiple failed attempts.\n";
    }
}

void Account::resetFailedAttempts() {
    failedAttempts = 0;
}

bool Account::getLockStatus() {
    return isLocked;
}

void Account::lockAccount() {
    isLocked = true;
}