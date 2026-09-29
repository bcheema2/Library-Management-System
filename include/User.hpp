//
// Created by Bibenpreet Cheema on 9/28/26.
//

#pragma once
#include <string>

class User {
    private:
    std::string username;
    std::string name;
    std::string email;
    std::string role;

    public:
    User() = default;
    User(std::string& username, std::string& name, std::string& email, std::string& role):
                username(std::move(username)),
                name(std::move(name)),
                email(std::move(email)),
                role(std::move(role)) {}
    virtual ~User() = default;

    //Getters
    [[nodiscard]]std::string getUsername() const noexcept {return username;};
    [[nodiscard]]std::string getName() const noexcept {return name;};
    [[nodiscard]]std::string getEmail() const noexcept {return email;};
    [[nodiscard]]std::string getRole() const noexcept {return role;};

};
