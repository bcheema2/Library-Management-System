//
// Created by Bibenpreet Cheema on 10/2/26.
//
#include "Transaction.hpp"

Transaction::Transaction(std::string transactionID, const User& user, const Book& book):
            transactionId{std::move(transactionID)},
            username(user.getUsername()),
            ISBN(book.getISBN()),
            issueDate(std::chrono::system_clock::now()),
            dueDate(issueDate + std::chrono::days(user.borrowLimit())),
            isReturned(false)  {}

double Transaction::getFineAmount(const User& user) {
    if (isReturned == false && (dueDate - issueDate > std::chrono::days(user.borrowLimit()))) {
        const auto duration = std::chrono::duration_cast<std::chrono::days>(dueDate - issueDate);
        fineAmount = duration.count() * 5.00;
    }
    return fineAmount ;
}


