# C++ Banking System

## Overview
A command-line banking system built in C++ that demonstrates object-oriented programming, file handling, and persistent data storage across sessions.

## Features
- Account creation and login
- Deposit and withdrawal
- Balance checking
- Transaction logging with timestamps
- Persistent data storage using files
- Account lock after multiple failed login attempts
- Masked PIN input for secure authentication

## Tech Stack
- C++
- OOP (Classes, Encapsulation)
- File Handling

## Project Structure
- src/ → source files
- include/ → header files
- data/ → stored data files

## Data Storage
- Accounts stored in: data/accounts.txt
- Transactions stored in: data/transactions.txt

## How to Run

### Compile
g++ src/*.cpp -o bank

### Run
./bank

