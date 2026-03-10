#include "../include/wallet_service.hpp"
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

namespace {
int readMenuChoice() {
    int choice = 0;

    std::cout << "\n=== E-Wallet Management Console ===\n";
    std::cout << "1. Register user\n";
    std::cout << "2. Add funds\n";
    std::cout << "3. Withdraw funds\n";
    std::cout << "4. Transfer funds\n";
    std::cout << "5. View balance\n";
    std::cout << "6. List users\n";
    std::cout << "7. View transaction history\n";
    std::cout << "8. Save and exit\n";
    std::cout << "Choose an option: ";

    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}

std::string readLine(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

double readAmount(const std::string& prompt) {
    double amount = 0.0;

    while (true) {
        std::cout << prompt;
        if (std::cin >> amount) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return amount;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid amount. Try again.\n";
    }
}

void printTransactions(const std::vector<Transaction>& transactions) {
    if (transactions.empty()) {
        std::cout << "No transactions recorded.\n";
        return;
    }

    std::cout << "\nRecent transactions\n";
    for (const Transaction& transaction : transactions) {
        std::cout << "- [" << transaction.type << "] "
                  << transaction.from << " -> " << transaction.to
                  << " : $" << std::fixed << std::setprecision(2) << transaction.amount
                  << " at " << transaction.timestamp << "\n";
    }
}
}

int main() {
    WalletService wallet;

    while (true) {
        const int choice = readMenuChoice();

        switch (choice) {
        case 1:
        {
            const std::string name = readLine("Name: ");
            const std::string email = readLine("Email: ");

            if (wallet.registerUser(name, email)) {
                std::cout << "User created.\n";
            } else {
                std::cout << "User could not be created.\n";
            }
            break;
        }

        case 2:
        {
            const std::string email = readLine("Email: ");
            const double amount = readAmount("Amount: ");

            if (wallet.addFunds(email, amount)) {
                std::cout << "Funds added.\n";
            } else {
                std::cout << "Unable to add funds.\n";
            }
            break;
        }

        case 3:
        {
            const std::string email = readLine("Email: ");
            const double amount = readAmount("Amount: ");

            if (wallet.withdrawFunds(email, amount)) {
                std::cout << "Withdrawal complete.\n";
            } else {
                std::cout << "Withdrawal failed.\n";
            }
            break;
        }

        case 4:
        {
            const std::string from = readLine("From email: ");
            const std::string to = readLine("To email: ");
            const double amount = readAmount("Amount: ");

            if (wallet.transferFunds(from, to, amount)) {
                std::cout << "Transfer complete.\n";
            } else {
                std::cout << "Transfer failed.\n";
            }
            break;
        }

        case 5:
        {
            const std::string email = readLine("Email: ");
            const double balance = wallet.getBalance(email);

            if (balance < 0) {
                std::cout << "User not found.\n";
            } else {
                std::cout << "Balance: $" << std::fixed << std::setprecision(2) << balance << "\n";
            }
            break;
        }

        case 6:
            wallet.printUsers();
            break;

        case 7:
            printTransactions(wallet.getTransactions());
            break;

        case 8:
            wallet.save();
            return 0;

        default:
            std::cout << "Invalid option.\n";
            break;
        }
    }
}
