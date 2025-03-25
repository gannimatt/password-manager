#include "PasswordEntry.h"
#include <iostream>

PasswordEntry::PasswordEntry(const std::string& name, const std::string& password, const std::string& category,
                             const std::string& website, const std::string& login) :
        name(name), password(password), category(category), website(website), login(login) {}

std::string PasswordEntry::getName() const {
    return name;
}

std::string PasswordEntry::getPassword() const {
    return password;
}

std::string PasswordEntry::getCategory() const {
    return category;
}

std::string PasswordEntry::getWebsite() const {
    return website;
}

std::string PasswordEntry::getLogin() const {
    return login;
}

void PasswordEntry::setPassword(const std::string& newPassword) {
    password = newPassword;
}
