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
static std::vector<std::string> stringParser(const std::string str , char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream tokenStream(str);

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void StorageManager::loadBook(std::unordered_map<std::string,std::unique_ptr<Book>>& books) {
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

            auto book = std::make_unique<Book>(isbn, author, category, bookName, isAvailable);
            books[isbn] = std::move(book);
        }
    }
    bookFile.close();
    fmt::print("Successfully loaded from books.txt\n");
}

void StorageManager::saveUsers(std::unordered_map<std::string, std::shared_ptr<User> >& users) {
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
                user = std::make_shared<Admin>(name, email, username,role);
            }
            else if (role == User::Role::Student) {
                user = std::make_shared<Student>(name, email, username,role);
            }

            if (user != nullptr) {
                users[username] = user;
            }
        }
    }
    usersFile.close();
    fmt::print("Successfully loaded from users.txt\n");
}

