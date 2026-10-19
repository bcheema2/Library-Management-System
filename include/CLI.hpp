//
// Created by Bibenpreet Cheema on 10/19/26.
//

#pragma once
#include "Catalog.hpp"

class CLI {
    Catalog& catalog;

    void adminMenu(const std::shared_ptr<User>& admin);
    void studentMenu(const std::shared_ptr<User>& student);
    static int getValidatedInt();


    public:
    explicit CLI(Catalog& cat);
    void start();

    ~CLI() = default;
};
