#include "../include/BankSystem.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <conio.h>   // for _getch()

using namespace std;

string getMaskedPIN() {
    string pin = "";
    char ch;

    while (true) {
        ch = _getch();

        if (ch == 13) break; 

        if (ch == 8) { 
            if (!pin.empty()) {
                pin.pop_back();
                cout << "\b \b";
            }
        } else {
            pin.push_back(ch);
            cout << "*";
        }
    }
    cout << endl;
    return pin;
}

BankSystem::BankSystem() {
    loadData();
}

void BankSystem::loadData() {
    accounts.clear();
    ifstream file("data/accounts.txt");

    if (!file.is_open()) {
        cout << "No previous data found.\n";
        return;
    }

    int accNo;
    string name, pin;
    double balance;
    bool isLocked;

    while (file >> accNo >> name >> pin >> balance >> isLocked) {

        if (accNo <= 0) continue;

        Account acc(accNo, name, pin, balance);
        if (isLocked) acc.lockAccount();
        accounts.push_back(acc);
    }
    file.close();
}

void BankSystem::saveData() {
    ofstream file("data/accounts.txt");
    for (auto &acc : accounts) {
        file << acc.getAccNo() << " "
             << acc.getName() << " "
             << acc.getPin() << " "
             << acc.getBalance() << " "
             << acc.getLockStatus() << endl;
    }
}

void BankSystem::createAccount() {
    int accNo;
    string name;

    cout << "Enter Account No: ";
    cin >> accNo;

    if (accNo <= 0) {
        cout << "Invalid account number\n";
        return;
    }

    for (auto &acc : accounts) {
        if (acc.getAccNo() == accNo) {
            cout << "Account number already exists!\n";
            return;
        }
    }

    cout << "Enter Name: ";
    cin >> name;

    cout << "Set PIN: ";
    string inputPin = getMaskedPIN();
    int pin = stoi(inputPin);

    accounts.push_back(Account(accNo, name, pin));

    cout << "Account Created!\n";
    saveData();
}

string encryptPIN(int pin);
Account* BankSystem::login() {
    int accNo;
    cout << "Enter Account No: ";
    cin >> accNo;

    if (cin.fail()) {
        cout << "Invalid account number\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return nullptr;
    }

    for (auto &acc : accounts) {
        if (acc.getAccNo() == accNo) {

            if (acc.getLockStatus()) {
                cout << "Account is locked. Contact admin.\n";
                return nullptr;
            }

            int attemptsLeft = 3;

            while (attemptsLeft--) {
                cout << "Enter PIN: ";
                string inputPin = getMaskedPIN();
                int pin = stoi(inputPin);

                if (acc.getPin() == encryptPIN(pin)) {
                    cout << "Login successful\n";
                    acc.resetFailedAttempts();
                    return &acc;
                } else {
                    acc.incrementFailedAttempts();

                    if (attemptsLeft > 0) {
                        cout << "Incorrect PIN. Attempts left: " << attemptsLeft << endl;
                    }
                }

                if (acc.getLockStatus()) {
                    return nullptr;
                }
            }

            return nullptr;
        }
    }

    cout << "Account not found\n";
    return nullptr;
}

void BankSystem::deposit(Account* acc) {
    double amt;
    cout << "Enter amount: ";
    cin >> amt;
    if (cin.fail() || amt <= 0) {
        cout << "Invalid amount\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }
    cin.ignore(1000, '\n');

    acc->deposit(amt);  
    logTransaction(acc->getAccNo(), "Deposit", amt);
    saveData();
    cout << "Deposit successful\n";
}

void BankSystem::withdraw(Account* acc) {
    double amt;
    cout << "Enter amount: ";
    cin >> amt;

    if (cin.fail() || amt <= 0) {
        cout << "Invalid amount\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }
    cin.ignore(1000, '\n');

    if (acc->withdraw(amt)) {
        logTransaction(acc->getAccNo(), "Withdraw", amt);
        saveData();
        cout << "Withdraw successful\n";
    } else {
        cout << "Insufficient balance\n";
    }
}


void BankSystem::logTransaction(int accNo, string type, double amt) {
    ofstream file("data/transactions.txt", ios::app);

    time_t now = time(0);
    tm *ltm = localtime(&now);

    file << "["
         << 1900 + ltm->tm_year << "-"
         << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-"
         << setw(2) << setfill('0') << ltm->tm_mday << " "
         << setw(2) << setfill('0') << ltm->tm_hour << ":"
         << setw(2) << setfill('0') << ltm->tm_min << ":"
         << setw(2) << setfill('0') << ltm->tm_sec
         << "] "
         << accNo << " " << type << " "
         << fixed << setprecision(2) << amt << endl;
}

void BankSystem::showBalance(Account* acc) {
    cout << "Current Balance: " << acc->getBalance() << endl;
}

void viewTransactions(int accNo) {
    ifstream file("data/transactions.txt");

    string line;
    bool found = false;

    while (getline(file, line)) {
        
        size_t pos = line.find("]");

        if (pos != string::npos) {
            string remaining = line.substr(pos + 2); 

            int fileAccNo = stoi(remaining);

            if (fileAccNo == accNo) {
                cout << line << endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "No transactions found\n";
    }

    file.close();
}

void BankSystem::transfer(Account* sender) {
    int receiverAccNo;
    double amt;

    cout << "Enter receiver account number: ";
    cin >> receiverAccNo;

    if (cin.fail()) {
        cout << "Invalid account number\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    Account* receiver = nullptr;

    for (auto &acc : accounts) {
        if (acc.getAccNo() == receiverAccNo) {
            receiver = &acc;
            break;
        }
    }

    if (receiver == nullptr) {
        cout << "Receiver account not found\n";
        return;
    }

    if (receiver->getAccNo() == sender->getAccNo()) {
        cout << "Cannot transfer to same account\n";
        return;
    }

    cout << "Enter amount: ";
    cin >> amt;

    if (cin.fail() || amt <= 0) {
        cout << "Invalid amount\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    cin.ignore(1000, '\n');

    if (!sender->withdraw(amt)) {
        cout << "Insufficient balance\n";
        return;
    }

    receiver->deposit(amt);

    logTransaction(sender->getAccNo(), "Transfer-Sent", amt);
    logTransaction(receiver->getAccNo(), "Transfer-Received", amt);

    saveData();

    cout << "Transfer successful\n";
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

void BankSystem::showAllAccounts() {
    for (auto &acc : accounts) {
        cout << "Acc No: " << acc.getAccNo()
             << " | Name: " << acc.getName()
             << " | Balance: " << acc.getBalance() << endl;
    }
}

void BankSystem::totalBankBalance() {
    double total = 0;
    for (auto &acc : accounts) {
        total += acc.getBalance();
    }
    cout << "Total Bank Balance: " << total << endl;
}

void BankSystem::unlockAccount() {
    int accNo;
    cout << "Enter account number to unlock: ";
    cin >> accNo;

    for (auto &acc : accounts) {
        if (acc.getAccNo() == accNo) {
            acc.unlockAccount();
            saveData();  // persist change
            cout << "Account unlocked successfully\n";
            return;
        }
    }
    cout << "Account not found\n";
}

void BankSystem::showTotalUsers() {
    cout << "Total Users: " << accounts.size() << endl;
}

void BankSystem::showRichestAccount() {
    if (accounts.empty()) {
        cout << "No accounts available\n";
        return;
    }

    Account* rich = &accounts[0];

    for (auto &acc : accounts) {
        if (acc.getBalance() > rich->getBalance()) {
            rich = &acc;
        }
    }

    cout << "Richest Account:\n";
    cout << "Acc No: " << rich->getAccNo() << endl;
    cout << "Name: " << rich->getName() << endl;
    cout << "Balance: " << rich->getBalance() << endl;
}