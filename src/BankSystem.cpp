#include "../include/BankSystem.h"
#include <fstream>
#include <iostream>
#include <ctime>

using namespace std;

void logTransaction(int accNo, string type, double amt) {
    ofstream file("../data/transactions.txt", ios::app);
    time_t now = time(0);
    file << ctime(&now) << " | Acc: " << accNo 
         << " | " << type << " | " << amt << endl;
}

void BankSystem::loadData() {
    ifstream file("../data/accounts.dat");
    int accNo, pin;
    string name;
    double balance;

    while (file >> accNo >> name >> pin >> balance) {
        Account acc(accNo, name, pin);
        acc.deposit(balance);
        accounts.push_back(acc);
    }
}

void BankSystem::saveData() {
    ofstream file("../data/accounts.dat");
    for (auto &acc : accounts) {
        file << acc.getAccNo() << " "
             << acc.getName() << " "
             << acc.getPin() << " "
             << acc.getBalance() << endl;
    }
}

void BankSystem::createAccount() {
    int accNo, pin;
    string name;

    cout << "Enter Account No: ";
    cin >> accNo;

    for (auto &acc : accounts) {
        if (acc.getAccNo() == accNo) {
            cout << "Account number already exists!\n";
            return;
        }
    }

    cout << "Enter Name: ";
    cin >> name;

    cout << "Set PIN: ";
    cin >> pin;

    accounts.push_back(Account(accNo, name, pin));
    cout << "Account Created!\n";
}

Account* BankSystem::login() {
    int accNo, pin, attempts = 3;

    while (attempts--) {
        cout << "Enter Account No: ";
        cin >> accNo;
        cout << "Enter PIN: ";
        cin >> pin;

        for (auto &acc : accounts) {
            if (acc.getAccNo() == accNo && acc.getPin() == pin) {
                cout << "Login Successful\n";
                return &acc;
            }
        }
        cout << "Invalid. Attempts left: " << attempts << endl;
    }
    return nullptr;
}

void BankSystem::deposit(Account* acc) {
    double amt;
    cout << "Enter amount: ";
    cin >> amt;

    acc->deposit(amt);
    logTransaction(acc->getAccNo(), "Deposit", amt);
}

void BankSystem::withdraw(Account* acc) {
    double amt;
    cout << "Enter amount: ";
    cin >> amt;

    if (acc->withdraw(amt)) {
        logTransaction(acc->getAccNo(), "Withdraw", amt);
    } else {
        cout << "Insufficient balance\n";
    }
}

void BankSystem::showBalance(Account* acc) {
    cout << "Balance: " << acc->getBalance() << endl;
}

void viewTransactions(int accNo) {
    ifstream file("../data/transactions.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line.find(to_string(accNo)) != string::npos) {
            cout << line << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No transactions found.\n";
    }
}

void BankSystem::searchAccount() {
    int accNo;
    cout << "Enter Account Number to search: ";
    cin >> accNo;

    for (auto &acc : accounts) {
        if (acc.getAccNo() == accNo) {
            cout << "Account Found:\n";
            cout << "Name: " << acc.getName() << endl;
            cout << "Balance: " << acc.getBalance() << endl;
            return;
        }
    }

    cout << "Account not found.\n";
}