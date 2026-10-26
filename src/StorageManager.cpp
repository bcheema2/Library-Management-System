//
// Created by Bibenpreet Cheema on 10/18/26.
//
#include "StorageManager.hpp"
#include <fstream>
#include "fmt/core.h"
#include <sstream>
#include <memory>
#include "User.hpp"

void StorageManager::saveBook(std::unordered_map<std::string, std::unique_ptr<Book>>& books) {
    // Make a file for books where we save book (members separated using |)
    std::ofstream bookFile("books.txt");
    if (bookFile.is_open()) {
        for (const auto& [isbn, book] : books) {
            bookFile << book->getISBN() << '|'
                     << book->getAuthor() << '|'
                     << book->getBookName() << '|'
                     << book->getCategory() << '|'
                     << (book->available() ? "true" : "false") << '\n';
        }
    }
    else {
        fmt::print("Cannot open books.txt\n");
        return;
    }
    bookFile.close();
}
//Helper Function to parse out String from file
static std::vector<std::string> stringParser(const std::string& str ,const char delimiter) {
    // Will be a little identical to coding decoding problem on Neetcode
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream tokenStream(str);

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void StorageManager::loadBook(std::unordered_map<std::string,std::unique_ptr<Book>>& books) {
    // This is just reverse of saving book
    std::ifstream bookFile("books.txt");
    if (!bookFile.is_open()) {
        fmt::print("Cannot open books.txt\n");
        return;
    }
    if (bookFile.peek() == std::ifstream::traits_type::eof()) {
        fmt::print("File is empty\n");
        return;
    }
    std::string line;
    while (std::getline(bookFile, line)) {
        std::vector<std::string> token = stringParser(line, '|');
        if (token.size() == 5) {
            std::string isbn = token[0];
            std::string author = token[1];
            std::string bookName = token[2];
            std::string category = token[3];
            bool isAvailable = (token[4] == "true");

            auto book = std::make_unique<Book>(isbn, author, bookName, category, isAvailable);
            books[isbn] = std::move(book);
        }
    }
    bookFile.close();
    fmt::print("Successfully loaded from books.txt\n");
}

void StorageManager::saveUsers(std::unordered_map<std::string, std::shared_ptr<User> >& users) {
    //Mostly same as users file
    std::ofstream usersFile("users.txt");
    if (!usersFile.is_open()) {
        fmt::print("Cannot open file : users.txt\n");
        return;
    }
    for (const auto& [username, user] : users) {
        usersFile << user->getUsername() << '|'
                  << user->getName() << '|'
                  << user->getEmail() << '|'
                  << static_cast<int>(user->getRole()) << '\n';
    }
    usersFile.close();
}

void StorageManager::loadUsers(std::unordered_map<std::string, std::shared_ptr<User> >& users) {
    std::ifstream usersFile("users.txt");
    if (!usersFile.is_open()) {
        fmt::print("Cannot load file: users.txt\n");
        return;
    }
    if (usersFile.peek() == std::ifstream::traits_type::eof()) {
        fmt::print("File is empty\n");
        return;
    }
    std::string line;
    while (std::getline(usersFile, line)) {
        std::vector<std::string> token = stringParser(line, '|');
        if (token.size() == 4) {
            std::string username = token[0];
            std::string name = token[1];
            std::string email = token[2];
            auto role = static_cast<User::Role>(std::stoi(token[3]));

            std::shared_ptr<User> user = nullptr;

            if (role == User::Role::Admin) {
                user = std::make_shared<Admin>(username, name, email,role);
            }
            else if (role == User::Role::Student) {
                user = std::make_shared<Student>(username, name, email,role);
            }

            if (user != nullptr) {
                users[username] = user;
            }
        }
    }
    usersFile.close();
    fmt::print("Successfully loaded from users.txt\n");
}

void StorageManager::saveTransaction(std::vector<Transaction>& transactions) {
    //First thing to do is load book.text to see if we have this book and is available is true
    std::ofstream transactionFile("transactions.txt");
    if (!transactionFile.is_open()) {
        fmt::print("Cannot open file : transactions.txt\n");
        return;
    }


    auto dueDate = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    for (const auto& transaction : transactions) {
        auto issueEpoch = std::chrono::duration_cast<std::chrono::seconds>(
        transaction.getIssueDate().time_since_epoch()).count();

        auto dueEpoch = std::chrono::duration_cast<std::chrono::seconds>(
            transaction.getDueDate().time_since_epoch()).count();
        transactionFile << transaction.getTransactionID() << '|'
                        << transaction.getUsername() << '|'
                        << transaction.getISBN() << '|'
                        << issueEpoch << '|'
                        << dueEpoch << '|'
                        << (transaction.getReturned() ? "true" : "false") << '\n';
    }

    transactionFile.close();

}

void StorageManager::loadTransaction(std::vector<Transaction>& transactions) {
    std::ifstream transactionFile("transactions.txt");
    if (!transactionFile.is_open()) {
        fmt::print("Cannot open file : transactions.txt\n");
        return;
    }
    if (transactionFile.peek() == std::ifstream::traits_type::eof()) {
        fmt::print("File is empty\n");
        return;
    }
    std::string line;
    while (std::getline(transactionFile, line)) {
        std::vector<std::string> token = stringParser(line, '|');
        if (token.size() == 6) {
            std::string transactionID = token[0];
            std::string username = token[1];
            std::string isbn = token[2];
            auto issueSecs = std::chrono::seconds(std::stoll(token[3]));
            auto dueSecs = std::chrono::seconds(std::stoll(token[4]));
            std::chrono::system_clock::time_point issueDate(issueSecs);
            std::chrono::system_clock::time_point dueDate(dueSecs);
            bool isReturned = (token[5] == "true");

            transactions.emplace_back(transactionID, username, isbn, issueDate, dueDate, isReturned);
        }
    }

    transactionFile.close();
    fmt::print("Successfully loaded from transactions.txt\n");
}

