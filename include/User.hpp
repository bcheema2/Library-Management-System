//
// Created by Bibenpreet Cheema on 9/28/26.
//

#pragma once
#include <string>


class User {
    public:
    enum class Role {
        Admin,
        Student
    };
    private:
    std::string username;
    std::string name;
    std::string email;
    Role role;
    int borrow = 0;

    public:
    User() = default;
    User(std::string username, std::string name, std::string email,Role r):
                username(std::move(username)),
                name(std::move(name)),
                email(std::move(email)),
                role(r)
                 {}
    virtual ~User() = default;

    //Getters
    [[nodiscard]]std::string getUsername() const noexcept {return username;};
    [[nodiscard]]std::string getName() const noexcept {return name;};
    [[nodiscard]]std::string getEmail() const noexcept {return email;};
    [[nodiscard]] int getBorrow() const noexcept {return borrow;};

    void setBorrow(int value) {
        borrow = value;
    }
    [[nodiscard]] virtual int borrowLimit() const = 0;
};

