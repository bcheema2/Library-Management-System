//
// Created by Bibenpreet Cheema on 9/30/26.
//
#include "Catalog.hpp"
#include <fmt/core.h>
#include <print>
void Catalog::addBook(std::unique_ptr<Book> books) {
    if (books) {
        std::string isbn = books->getISBN();
        bookByISBN.emplace(std::move(isbn), std::move(books));
        fmt::print("Successfully added book: {}\n", isbn);
    }
    fmt::print("Failed to add book: {}. Book already exists.\n",books->getISBN());
}


