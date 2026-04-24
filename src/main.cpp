#include "../include/BankSystem.h"
#include <iostream>
using namespace std;

void viewTransactions(int accNo);
int main() {
    BankSystem bank;
    bank.loadData();

    int choice;

    do {
        cout << "\n1. Create Account\n2. Login\n3. Search Account\n4. Exit\n";
        cin >> choice;

        if (choice == 1) {
            bank.createAccount();
        } 
        else if (choice == 2) {
            Account* user = bank.login();
            if (user) {
                int opt;
                do {
                    cout << "\n1. Balance\n2. Deposit\n3. Withdraw\n4. Transactions\n5. Logout\n";
                    cin >> opt;

                    if (opt == 1) bank.showBalance(user);
                    else if (opt == 2) bank.deposit(user);
                    else if (opt == 3) bank.withdraw(user);
                    else if (opt == 4) viewTransactions(user->getAccNo());

                } while (opt != 5);
            }
        }
        else if(choice == 3){
            bank.searchAccount();
        }

    } while (choice != 4);

    bank.saveData();
    return 0;
}