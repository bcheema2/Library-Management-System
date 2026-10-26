//
// Created by Bibenpreet Cheema on 10/14/26.
//

#pragma once

#include "Catalog.hpp"
#include "Book.hpp"
#include "User.hpp"

class StorageManager {
  public:
  StorageManager() = default;

  static void saveBook(std::unordered_map<std::string, std::unique_ptr<Book>>& books);

  static void loadBook(std::unordered_map<std::string, std::unique_ptr<Book>>& books);

  static void saveUsers(std::unordered_map<std::string, std::shared_ptr<User>>& users);

  static void loadUsers(std::unordered_map<std::string, std::shared_ptr<User>>& users);

  static void saveTransaction(std::vector<Transaction>& transactions);

  static void loadTransaction(std::vector<Transaction>& transactions);
};
