//
// Created by Bibenpreet Cheema on 10/2/26.
//
#include "Transaction.hpp"

Transaction::Transaction(std::string transactionID, const User& user, const Book& book):
            transactionId{std::move(transactionID)},
            username(user.getUsername()),
            ISBN(book.getISBN()) {}


