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
    std::string transactionId;
    std::string username;
    std::string ISBN;
    std::chrono::system_clock::time_point issueDate;
    std::chrono::system_clock::time_point dueDate;
    std::chrono::system_clock::time_point returnDate;
    double fineAmount{0.0};
    bool isReturned{true};

    public:
    Transaction() = default;

    Transaction( std::string transactionID, const User& user, const Book& book);

    double getFineAmount(const User& user);
};


