#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <ctime>
#include <string>

struct Transaction {
    std::string type;
    std::string from;
    std::string to;
    double amount;
    std::time_t timestamp;

    Transaction()
        : amount(0.0), timestamp(std::time(nullptr)) {}

    Transaction(const std::string& transactionType,
                const std::string& sender,
                const std::string& recipient,
                double value,
                std::time_t occurredAt = std::time(nullptr))
        : type(transactionType),
          from(sender),
          to(recipient),
          amount(value),
          timestamp(occurredAt) {}
};

#endif
