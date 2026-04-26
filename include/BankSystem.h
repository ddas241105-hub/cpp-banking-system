#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include "Account.h"
#include <vector>

class BankSystem {
    public:
    BankSystem();   
private:
    std::vector<Account> accounts;

public:
    void loadData();
    void saveData();

    void createAccount();
    Account* login();

    void deposit(Account*);
    void withdraw(Account*);
    void logTransaction(int, string, double);
    void showBalance(Account*);
    void searchAccount();
    void transfer(Account* sender);
    void showAllAccounts();
    void totalBankBalance();
    void unlockAccount();
    void showTotalUsers();
    void showRichestAccount();   
};

#endif