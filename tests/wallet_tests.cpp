#include "../include/wallet_service.hpp"
#include <filesystem>
#include <iostream>
#include <stdexcept>

namespace {
void require(bool condition, const std::string& message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}
}

int main() {
    const std::filesystem::path testDataDirectory =
        std::filesystem::temp_directory_path() / "ewallet-management-tests";
    std::error_code cleanupError;
    std::filesystem::remove_all(testDataDirectory, cleanupError);

    try {
        WalletService wallet(testDataDirectory);

        require(wallet.registerUser("Alice", "alice@example.com"), "registering Alice should succeed");
        require(wallet.registerUser("Bob", "bob@example.com"), "registering Bob should succeed");
        require(!wallet.registerUser("Duplicate Bob", "bob@example.com"), "duplicate email must fail");
        require(!wallet.registerUser("Invalid", "not-an-email"), "invalid email must fail");

        require(wallet.addFunds("alice@example.com", 250.0), "deposit should succeed");
        require(!wallet.addFunds("missing@example.com", 10.0), "deposit to unknown user must fail");
        require(wallet.transferFunds("alice@example.com", "bob@example.com", 100.0), "transfer should succeed");
        require(!wallet.transferFunds("alice@example.com", "bob@example.com", 500.0), "overdraft transfer must fail");
        require(wallet.withdrawFunds("bob@example.com", 50.0), "withdrawal should succeed");

        require(wallet.getBalance("alice@example.com") == 150.0, "Alice balance should be 150");
        require(wallet.getBalance("bob@example.com") == 50.0, "Bob balance should be 50");
        require(wallet.getTransactions().size() == 3, "three successful transactions should be recorded");

        wallet.save();

        WalletService reloadedWallet(testDataDirectory);
        require(reloadedWallet.userExists("alice@example.com"), "reloaded wallet should contain Alice");
        require(reloadedWallet.getBalance("alice@example.com") == 150.0, "Alice balance should persist");
        require(reloadedWallet.getBalance("bob@example.com") == 50.0, "Bob balance should persist");
        require(reloadedWallet.getTransactions().size() == 3, "transactions should persist");
    } catch (const std::exception& error) {
        std::cerr << "Test failure: " << error.what() << '\n';
        std::filesystem::remove_all(testDataDirectory, cleanupError);
        return 1;
    }

    std::filesystem::remove_all(testDataDirectory, cleanupError);
    std::cout << "All wallet tests passed.\n";
    return 0;
}
