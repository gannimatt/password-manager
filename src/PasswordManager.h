#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <string>
#include <vector>
#include "PasswordEntry.h"

class PasswordManager {
public:

    void userFileChoice();
    void run();
    bool loadPasswordsFromFile();

private:

    std::vector<PasswordEntry> passwords;
    std::string sourceFile;
    std::vector<std::string> usedPasswords;

    std::vector<PasswordEntry> passwordEntries;
    std::vector<std::string> categories;

    std::string filePath;

    std::string generateRandomPassword(int length, bool includeUppercase, bool includeLowercase, bool includeSpecialChars, bool includeNumbers);

    bool checkPasswordStrength(const std::string& password);
    bool checkIfPasswordUsedBefore(const std::string& password);


    void writePasswordsToFile();
    void readPasswordsFromFile();
    void saveCategories();
    void loadCategories();


    void savePasswords();
    void displayMenu();
    void executeCommand(int choice);
    void searchPasswords();
    void sortPasswords();
    void addPassword();
    void editPassword();
    void deletePassword();
    void addCategory();
    void deleteCategory();

};

#endif // PASSWORDMANAGER_H
