//
// Created by Bibenpreet Cheema on 10/2/26.
//
#include "Transaction.hpp"
Transaction::Transaction(User& user, Book& book) :
            username(user.getUsername()),
            ISBN(book.getISBN()),
            issueDate(std::chrono::system_clock::now()),
            dueDate(issueDate + std::chrono::days(user.borrowLimit())) {
            transactionID = "TXN" + username + " " + ISBN;
}
Transaction::Transaction(std::string txID, std::string uname, std::string isbn,
                         std::chrono::system_clock::time_point issue,
                         std::chrono::system_clock::time_point due,
                         bool returned) :
    transactionID(std::move(txID)),
    username(std::move(uname)),
    ISBN(std::move(isbn)),
    issueDate(issue),
    dueDate(due),
    isReturned(returned) {}

double Transaction::getFineAmount() {
    auto now = std::chrono::system_clock::now();
    if (isReturned == false && now > dueDate) {
        const auto duration = std::chrono::duration_cast<std::chrono::days>(now - dueDate);
        fineAmount = duration.count() * 5.00;
    }
    return fineAmount ;
}


