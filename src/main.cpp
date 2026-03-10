#include "../include/wallet_service.hpp"
#include <iostream>

int main() {

    WalletService wallet;

    int choice;

    while (true) {

        std::cout << "\n=== E-Wallet System ===\n";
        std::cout << "1 Register User\n";
        std::cout << "2 Add Funds\n";
        std::cout << "3 Transfer Funds\n";
        std::cout << "4 View Balance\n";
        std::cout << "5 Exit\n";

        std::cin >> choice;

        std::string name, email, to;
        double amount;

        switch (choice) {

        case 1:

            std::cout << "Name: ";
            std::cin >> name;

            std::cout << "Email: ";
            std::cin >> email;

            if (wallet.registerUser(name, email))
                std::cout << "User created\n";
            else
                std::cout << "User exists\n";

            break;

        case 2:

            std::cout << "Email: ";
            std::cin >> email;

            std::cout << "Amount: ";
            std::cin >> amount;

            if (wallet.addFunds(email, amount))
                std::cout << "Funds added\n";
            else
                std::cout << "Error\n";

            break;

        case 3:

            std::cout << "From: ";
            std::cin >> email;

            std::cout << "To: ";
            std::cin >> to;

            std::cout << "Amount: ";
            std::cin >> amount;

            if (wallet.transferFunds(email, to, amount))
                std::cout << "Transfer complete\n";
            else
                std::cout << "Transfer failed\n";

            break;

        case 4:

            std::cout << "Email: ";
            std::cin >> email;

            std::cout << "Balance: $" << wallet.getBalance(email) << "\n";

            break;

        case 5:

            wallet.save();
            return 0;
        }
    }
}