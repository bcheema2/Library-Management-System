//
// Created by Bibenpreet Cheema on 9/30/26.
//
#include "Catalog.hpp"
#include <fmt/core.h>
#include <ranges>

void Catalog::addBook(std::unique_ptr<Book> book) {
    if (!book) {
        return;
    }
    std::string isbn = book->getISBN();
    const std::string author = book->getNormalizedAuthor();
    auto[iterator, inserted] = bookByISBN.try_emplace(isbn, std::move(book));

    if (inserted) {
        authorIndex[author].push_back(isbn);
        fmt::print("Successfully added book: {}\n", isbn);
    }
    else {
        fmt::print("Failed to add book: {}. Book already exists.\n",isbn);
    }
}

void Catalog::removeBook(const std::string& isbn) {
    // Author Lookup using ISBN key in bookByISBN to return book and then finding author.
    auto it = bookByISBN.find(isbn);
    if (it == bookByISBN.end()) {
        fmt::print("Failed to remove book: {}\n", isbn);
        return;
    }
    const std::string author = it->second->getNormalizedAuthor();
    auto ita = authorIndex.find(author);
    if (ita != authorIndex.end()) {
        auto& books = ita->second;
        std::erase(books, isbn);

        if (books.empty()) {
            authorIndex.erase(ita);
        }
    }
    bookByISBN.erase(isbn);
    fmt::print("Successfully removed book\n");
}


std::vector<const Book*> Catalog:: searchByTitle(const std::string& title) const {
    std::vector<const Book*> result;
    std::string cleanQuery = title;
    std::ranges::transform(cleanQuery, cleanQuery.begin(),
        [](const unsigned char c) { return std::tolower(c); });

    for (const auto &book: bookByISBN | std::views::values) {
        if (book) {
            if (book->getNormalizedTitle().find(cleanQuery) != std::string::npos) {
                result.push_back(book.get());
            }
        }
    }
    return result;
}

std::vector<const Book*> Catalog:: searchByAuthor(const std::string& author) const {
    std::vector<const Book*> result;
    std::string cleanQuery = author;
    std::ranges::transform(cleanQuery, cleanQuery.begin(),
        [](const unsigned char c) { return std::tolower(c); });

    auto it = authorIndex.find(cleanQuery);
    if (it != authorIndex.end()) {
        const std::vector<std::string>& isbns = it->second;
        for (const auto& isbn : isbns) {
            auto bookIt = bookByISBN.find(isbn);
            if (bookIt != bookByISBN.end() && bookIt->second) {
                result.push_back(bookIt->second.get());
            }
        }
    }
    return result;

}


bool Catalog::registerUser(std::unique_ptr<User> user) {
    if (!user) {
        fmt::print("Failed to register User\n");
        return false;
    }
    std::string userID = user->getUsername();
    auto [iterator, inserted] = userByUsername.try_emplace(userID, std::move(user));
    if (!inserted) {
        fmt::print("Username: {} already registered.\n", userID);
        return false;
    }
    fmt::print("Successfully registered user: {}\n", userID);
    return true;
}

std::shared_ptr<User> Catalog:: authenticateUser(const std::string& username) const {
    auto it = userByUsername.find(username);
    if (it == userByUsername.end()) {
        fmt::print("Username: {} does not exist.\n", username);
        return nullptr;
    }
    fmt::print("Successfully authenticated user: {}\n", username);
    return it->second;
}

bool Catalog::issueBook(const std::string &username, const std::string &isbn) {
    // Check username
    auto user = authenticateUser(username);
    if (!user) {
        return false;
    }
    //Check Book availability
    auto itb = bookByISBN.find(isbn);
    if (itb != bookByISBN.end() && itb->second->available() == true) {
        fmt::print("Successfully authenticated book: {}\n", isbn);
    }
    else if (itb == bookByISBN.end()) {
        fmt::print("No book available for isbn: {}\n", isbn);
        return false;
    }
    else if (itb->second->available() == false) {
        fmt::print("Book: {} is not available\n", isbn);
        return false;
    }

    int activeCount = 0;
    for (const auto& tx : activeTransactions) {
        if (tx.getUsername()== username && !tx.getReturned()) {
            activeCount++;
        }
    }

    int borrow = user->borrowLimit();

    if (activeCount >= borrow) {
        fmt::print("Borrow limit reached. Cannot issue another book");
        return false;
    }
    // Issue Book
    fmt::print("Book {} is issued to {}\n",isbn,username);
    itb->second->setAvailable(false);

    std::string txId = "TXN" + username + " " + isbn;
    Transaction newTX (txId, *user,*itb->second);
    activeTransactions.push_back(newTX);
    return true;
}

bool Catalog::returnBook(const std::string &username, const std::string &isbn) {

    for (const auto& tx : activeTransactions) {
        if (tx.getUsername() == username && tx.getISBN() == isbn && tx.getReturned() == false) {
            fmt::print("Transaction ID found");
        }
        else {
            fmt::print("Transaction ID not found");
            return false;
        }
    }
    
}
