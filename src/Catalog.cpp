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
        fmt::print("Failed to add book: {}. Book already exists.\n",book->getISBN());
    }
}

void Catalog::removeBook(const std::string& isbn) {
    // Author Lookup using ISBN key in bookByISBN to return book and then finding author.
    auto it = bookByISBN.find(isbn);
    if (it == bookByISBN.end()) {
        fmt::print("Failed to remove book: {}\n", isbn);
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
        const std::vector<std::string> isbns = it->second;
        for (const auto& isbn : isbns) {
            auto bookIt = bookByISBN.find(isbn);
            if (bookIt != bookByISBN.end() && bookIt->second) {
                result.push_back(bookIt->second.get());
            }
        }
    }
    return result;

}


