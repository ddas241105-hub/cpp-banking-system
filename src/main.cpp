#include "../include/BankSystem.h"
#include <iostream>
using namespace std;

void viewTransactions(int accNo);

int main() {
    BankSystem bank;
    bank.loadData();

    int choice;

    cout << "\n=============================\n";
    cout << "      BANK SYSTEM\n";
    cout << "=============================\n";

    do {
        cout << "\n1. Create Account\n2. Login\n3. Search Account\n4. Admin Login\n5. Exit\n";
        cin >> choice;
        if (cin.fail()) {
        cout << "Invalid input\n";
        cin.clear();
        cin.ignore(1000, '\n');
        continue;
        }
        cin.ignore(1000, '\n');

        if (choice == 1) {
            bank.createAccount();
        } 
        else if (choice == 2) {
            Account* user = bank.login();


        if (user) {
            int opt;
            do {
                cout << "\n1. Balance\n2. Deposit\n3. Withdraw\n4. Transactions\n5. Transfer Money\n6. Logout\n";
                 cin >> opt;

            if (cin.fail()) {
                cout << "Invalid input\n";
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }

            cin.ignore(1000, '\n');

            if (opt == 1) {
                bank.showBalance(user);
            } 
            else if (opt == 2) {
                bank.deposit(user);
            } 
            else if (opt == 3) {
                bank.withdraw(user);
            } 
            else if (opt == 4) {
                viewTransactions(user->getAccNo());
            } 
            else if (opt == 5) {   
                bank.transfer(user);
            } 
            else if (opt == 6) {
                cout << "Logging out...\n";
            } 
            else {
                cout << "Invalid option\n";
            }

        } while (opt != 6);     
    }
        }
        else if (choice == 3) {
            bank.searchAccount();
        }
        else if (choice == 4) {
            string adminUser, adminPass;

            cout << "Enter Admin Username: ";
            cin >> adminUser;

            cout << "Enter Admin Password: ";
            cin >> adminPass;

            if (adminUser == "admin" && adminPass == "1234") {
                cout << "\nAdmin Login Successful\n";

                int adminChoice;
                do {
                    cout << "\n====== ADMIN PANEL ======\n";
                    cout << "1. View All Accounts\n";
                    cout << "2. Search Account\n";
                    cout << "3. Total Bank Balance\n";
                    cout << "4. Unlock Account\n";
                    cout << "5. Total Users\n";
                    cout << "6. Richest Account\n";
                    cout << "7. Exit Admin Panel\n";
                    cin >> adminChoice;

                    if (cin.fail()) {
                        cout << "Invalid input\n";
                        cin.clear();
                        cin.ignore(1000, '\n');  
                        continue;
                    }

                    cin.ignore(1000, '\n');  
                     if (adminChoice == 1) {
                        bank.showAllAccounts();
                    }
                    else if (adminChoice == 2) {
                        bank.searchAccount();
                    }
                    else if (adminChoice == 3) {
                        bank.totalBankBalance();
                    }
                    else if (adminChoice == 4) {
                        bank.unlockAccount();
                    }
                    else if (adminChoice == 5) 
                        bank.showTotalUsers();
                    else if (adminChoice == 6) 
                        bank.showRichestAccount();
                    else if (adminChoice == 7)
                        break;
                }
                while (adminChoice != 4);
            } else {
                cout << "Invalid admin credentials\n";
            }
        }

    } while (choice != 5);

    bank.saveData();
    return 0;
}