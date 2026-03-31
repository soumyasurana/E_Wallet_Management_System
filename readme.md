# E-Wallet Management System

A clean and modular C++17 command-line application for managing digital wallets. This project lets users create accounts, handle transactions, and track balances with data stored persistently across runs. It’s designed with good structure, testability, and GitHub presentation in mind.

## 🚀 Highlights

* Create and manage wallet accounts with persistent storage
* Simple user registration with email validation
* Deposit, withdraw, and transfer funds بسهولة
* Track transaction history even after restarting the app
* Built using CMake for easy compilation and testing
* Integrated GitHub Actions CI for automated checks

## 📁 Project Structure

```
.
├── include/      # Header files
├── src/          # Core implementation
├── tests/        # Test cases
├── data/         # Stored runtime data
└── .github/      # CI workflows
```

## ⚙️ Build

```bash
cmake -S . -B build
cmake --build build
```

## ▶️ Run

```bash
./build/ewallet
```

By default, all data is saved in the `./data` folder.

## 🧪 Run Tests

```bash
ctest --test-dir build --output-on-failure
```

## ✅ What You Can Do

* Register new users
* Add money to wallets
* Withdraw funds
* Transfer money between users
* Check balances
* View all users
* Browse transaction history

## 🛠️ GitHub Ready

* Clean and portable CMake setup
* Modular code structure with reusable components
* Dedicated test suite
* CI pipeline for Linux builds
* Proper `.gitignore` and repo hygiene

## 🔮 What’s Next

* Switch to JSON or SQLite for storage
* Add authentication & user security
* Support multiple currencies
* Build a REST API or web interface

