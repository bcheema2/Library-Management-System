//
// Created by Bibenpreet Cheema on 9/30/26.
//

#pragma once

#include <Admin.hpp>
#include <Student.hpp>
#include <Book.hpp>
#include <chrono>
#include <User.hpp>

class Transaction {
    std::string username;
    std::string ISBN;
    std::chrono::system_clock::time_point issueDate;
    std::chrono::system_clock::time_point dueDate;
    std::chrono::system_clock::time_point returnDate;
    double fineAmount{0.0};
    bool isReturned{false};
    std::string transactionID;

public:
    Transaction() = default;
    Transaction(User& user, Book& book);
    Transaction(std::string txID, std::string uname, std::string isbn,
                         std::chrono::system_clock::time_point issue,
                         std::chrono::system_clock::time_point due,
                         bool returned);
    [[nodiscard]] const std::string& getUsername() const noexcept {return username;}
    [[nodiscard]] const std::string& getISBN() const noexcept {return ISBN;}
    [[nodiscard]] bool getReturned() const noexcept {return isReturned;}
    bool setReturned(bool status) {
        isReturned = status;
        return status;
    }
    [[nodiscard]] std::string getTransactionID() const noexcept {return transactionID;}
    [[nodiscard]] std::chrono::system_clock::time_point getIssueDate() const noexcept {return issueDate;}
    [[nodiscard]] std::chrono::system_clock::time_point getDueDate() const noexcept {return dueDate;}
    double getFineAmount();
};


