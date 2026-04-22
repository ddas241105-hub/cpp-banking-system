#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include "Account.h"
#include <vector>

class BankSystem {
private:
    std::vector<Account> accounts;

public:
    void loadData();
    void saveData();

    void createAccount();
    Account* login();

    void deposit(Account*);
    void withdraw(Account*);
    void showBalance(Account*);
};

#endif