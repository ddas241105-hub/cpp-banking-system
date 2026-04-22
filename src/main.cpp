#include "../include/BankSystem.h"
#include <iostream>
using namespace std;

int main() {
    BankSystem bank;
    bank.loadData();

    int choice;

    do {
        cout << "\n1. Create Account\n2. Login\n3. Exit\n";
        cin >> choice;

        if (choice == 1) {
            bank.createAccount();
        } 
        else if (choice == 2) {
            Account* user = bank.login();
            if (user) {
                int opt;
                do {
                    cout << "\n1. Balance\n2. Deposit\n3. Withdraw\n4. Logout\n";
                    cin >> opt;

                    if (opt == 1) bank.showBalance(user);
                    else if (opt == 2) bank.deposit(user);
                    else if (opt == 3) bank.withdraw(user);

                } while (opt != 4);
            }
        }

    } while (choice != 3);

    bank.saveData();
    return 0;
}