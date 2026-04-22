#include "../include/Account.h"

Account::Account() {}

Account::Account(int accNo, string name, int pin) {
    this->accNo = accNo;
    this->name = name;
    this->pin = pin;
    this->balance = 0;
}

int Account::getAccNo() { return accNo; }
string Account::getName() { return name; }
int Account::getPin() { return pin; }
double Account::getBalance() { return balance; }

void Account::deposit(double amt) {
    balance += amt;
}

bool Account::withdraw(double amt) {
    if (amt > balance) return false;
    balance -= amt;
    return true;
}