#ifndef PASSWORD_ENTRY_H
#define PASSWORD_ENTRY_H

#include <string>

class PasswordEntry {
public:

    PasswordEntry() = default;

    PasswordEntry(const std::string& name, const std::string& password, const std::string& category,
                  const std::string& website, const std::string& login);


    std::string getName() const;
    std::string getPassword() const;
    std::string getCategory() const;
    std::string getWebsite() const;
    std::string getLogin() const;

    void setPassword(const std::string& newPassword);

private:
    std::string name;
    std::string password;
    std::string category;
    std::string website;
    std::string login;

};

#endif // PASSWORD_ENTRY_H
