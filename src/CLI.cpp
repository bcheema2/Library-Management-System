//
// Created by Bibenpreet Cheema on 10/19/26.
//

#include "CLI.hpp"
#include <iostream>
#include <limits>
#include "fmt/core.h"

int CLI::getValidatedInt() {
    int choice = -1;
    while (true) {
        if (std::cin >> choice) {
            // Clear any trailing characters (like newline) from the buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        } else {
            // Reset the stream error flag and discard the invalid input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            fmt::print("Invalid input. Please enter a valid number: ");
        }
    }
}


CLI::CLI(Catalog& cat) : catalog(cat) {}

void CLI::start() {
    fmt::print("=== Welcome to the Library Management System ===\n");

    while (true) {
        fmt::print("\nEnter your username (or type 'exit' to quit): ");
        std::string username;
        std::getline(std::cin, username);

        if (username == "exit") {
            fmt::print("Shutting down system. Saving state...\n");
            break;
        }

        // Authenticate user against the catalog
        std::shared_ptr<User> currentUser = catalog.authenticateUser(username);

        if (currentUser == nullptr) {
            fmt::print("Error: User '{}' not found. Try again.\n", username);
            continue;
        }

        fmt::print("Login successful! Welcome, {}\n", currentUser->getName());

        // Route based on role
        if (currentUser->getRole() == User::Role::Admin) {
            adminMenu(currentUser);
        } else {
            studentMenu(currentUser);
        }
    }
}

void CLI::adminMenu(const std::shared_ptr<User>& admin) {
    while (true) {
        fmt::print("\n--- Admin Menu ---\n");
        fmt::print("1. Add Book\n");
        fmt::print("2. Remove Book\n");
        fmt::print("3. Register Member\n");
        fmt::print("4. View All Transactions\n");
        fmt::print("5. Logout\n");
        fmt::print("Select an option: ");

        int choice = getValidatedInt();

        if (choice == 1) {
            // --- Add Book Logic ---
            std::string isbn, title, author, category;
            fmt::print("Enter ISBN: ");
            std::getline(std::cin, isbn);
            fmt::print("Enter Book Title: ");
            std::getline(std::cin, title);
            fmt::print("Enter Author: ");
            std::getline(std::cin, author);
            fmt::print("Enter Category: ");
            std::getline(std::cin, category);

            // Create unique_ptr and pass to Catalog
            auto newBook = std::make_unique<Book>(isbn, author, category, title, true);
            catalog.addBook(std::move(newBook));
            fmt::print("Success: Book '{}' added to the catalog!\n", title);

        }
        else if (choice == 2) {
            // --- Remove Book Logic ---
            std::string isbn;
            fmt::print("Enter ISBN of the book to remove: ");
            std::getline(std::cin, isbn);
            catalog.removeBook(isbn);
            fmt::print("If the ISBN existed, the book has been removed.\n");

        }
        else if (choice == 3) {
            // --- Register Member Logic ---
            std::string username, name, email;
            fmt::print("Enter username: ");
            std::getline(std::cin, username);
            fmt::print("Enter full name: ");
            std::getline(std::cin, name);
            fmt::print("Enter email: ");
            std::getline(std::cin, email);

            fmt::print("Select Role (0 for Admin, 1 for Student): ");
            int roleInput = getValidatedInt();

            User::Role role = (roleInput == 0) ? User::Role::Admin : User::Role::Student;
            std::unique_ptr<User> newUser = nullptr;

            if (role == User::Role::Admin) {
                newUser = std::make_unique<Admin>(username, name, email, role);
            } else {
                newUser = std::make_unique<Student>(username, name, email, role);
            }

            if (catalog.registerUser(std::move(newUser))) {
                fmt::print("Success: User '{}' registered!\n", username);
            } else {
                fmt::print("Error: Username '{}' already exists.\n", username);
            }

        }
        else if (choice == 4) {
            fmt::print("\n--- Transactions View ---\n");
            fmt::print("Transaction history view under construction.\n");

        }
        else if (choice == 5) {
            fmt::print("Logging out...\n");
            break;
        }
        else {
            fmt::print("Invalid option. Please choose between 1 and 5.\n");
        }
    }
}

void CLI::studentMenu(const std::shared_ptr<User>& student) {
    while (true) {
        fmt::print("\n--- Student Menu ---\n");
        fmt::print("1. Search Catalog\n");
        fmt::print("2. Borrow Book\n");
        fmt::print("3. Return Book\n");
        fmt::print("4. View My Borrowed Books\n");
        fmt::print("5. Logout\n");
        fmt::print("Select an option: ");

        int choice = getValidatedInt();

        if (choice == 5) {
            fmt::print("Logging out...\n");
            break;
        }

        // Implement Student actions here...
        fmt::print("Feature under construction.\n");
    }
}
