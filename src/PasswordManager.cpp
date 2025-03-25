#include <iostream>
#include <fstream>
#include <filesystem>
#include <limits>
#include <random>
#include "PasswordManager.h"
#include "PasswordEntry.h"
#include <algorithm>


void PasswordManager::userFileChoice() {
    std::string folderPath = "files/password-files";
    int i = 1;

    std::cout << "Available files in the program's folder:" << std::endl;
    std::vector<std::string> validFileNames;
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            std::string fileName = entry.path().filename().string();
            if (fileName == "password.txt" || fileName == "password2.txt") {
                std::cout << i << ") " << fileName << std::endl;
                validFileNames.push_back(fileName);
                i++;

            }
        }
    }


    std::cout << "Enter the number corresponding to the file: ";
    int fileIndex;
    std::cin >> fileIndex;

    if (fileIndex >= 1 && fileIndex <= validFileNames.size()) {
        std::string fileName = validFileNames[fileIndex - 1];
        filePath = folderPath + "\\" + fileName;
        loadPasswordsFromFile();
        run();

    }
    else {
        std::cout << "Invalid file selection. Exiting..." << std::endl;
    }

}

void PasswordManager::writePasswordsToFile() {
    std::ofstream file(filePath, std::ios::app);
    if (file.is_open()) {
        for (const PasswordEntry& entry : passwords) {
            file << entry.getName() << "," << entry.getPassword() << "," << entry.getCategory() << ","
                 << entry.getWebsite() << "," << entry.getLogin() << std::endl;
        }
        file.close();
        std::cout << "Passwords appended to file." << std::endl;
    } else {
        std::cout << "Unable to open file for writing." << std::endl;
    }
}

void PasswordManager::readPasswordsFromFile() {


    std::ifstream file(filePath);
    if (file.is_open()) {
        passwords.clear();
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string name, password, category, website, login;
            std::getline(ss, name, ',');
            std::getline(ss, password, ',');
            std::getline(ss, category, ',');
            std::getline(ss, website, ',');
            std::getline(ss, login);

            PasswordEntry entry(name, password, category, website, login);
            passwords.push_back(entry);
        }
        file.close();
        std::cout << "Passwords loaded from file." << std::endl;
    } else {
        std::cout << "Unable to open file for reading." << std::endl;
    }
}

bool PasswordManager::loadPasswordsFromFile() {
    std::ifstream inputFile(filePath);

    if (!inputFile) {
        std::cout << "Failed to open the source file." << std::endl;
        return false;
    }

    std::string line;

    while (getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string name, password, category, website, login;
        if (getline(iss, name, ',') && getline(iss, password, ',') &&
            getline(iss, category, ',') && getline(iss, website, ',') && getline(iss, login)) {

            PasswordEntry entry(name, password, category, website, login);
            passwords.push_back(entry);
        }
    }

    inputFile.close();

    std::cout << "Passwords loaded successfully." << std::endl;
    return true;
}




void PasswordManager::run() {
    int choice;
    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        executeCommand(choice);

    } while (choice != 0);

}

void PasswordManager::savePasswords() {
    std::ofstream outputFile(filePath);
    if (!outputFile) {
        std::cout << "Failed to open the destination file." << std::endl;
        return;
    }

    for (const PasswordEntry& entry : passwords) {
        outputFile << entry.getName() << ","
                   << entry.getPassword() << ","
                   << entry.getCategory() << ","
                   << entry.getWebsite() << ","
                   << entry.getLogin() << "\n";
    }

    outputFile.close();

    std::cout << "Passwords saved successfully." << std::endl;
}

void PasswordManager::displayMenu() {
    std::cout << "---------------------\n";
    std::cout << "Password Manager\n";
    std::cout << "---------------------\n";
    std::cout << "1. Search Passwords\n";
    std::cout << "2. Sort Passwords\n";
    std::cout << "3. Add Password\n";
    std::cout << "4. Edit Password\n";
    std::cout << "5. Delete Password\n";
    std::cout << "6. Add Category\n";
    std::cout << "7. Delete Category\n";
    std::cout << "0. Exit\n";
    std::cout << "---------------------\n";
}

void PasswordManager::executeCommand(int choice) {
    switch (choice) {
        case 1:
            searchPasswords();
            break;
        case 2:
            sortPasswords();
            break;
        case 3:
            addPassword();
            break;
        case 4:
            editPassword();
            break;
        case 5:
            deletePassword();
            break;
        case 6:
            addCategory();
            break;
        case 7:
            deleteCategory();
            break;
        case 0:
            std::cout << "Exiting Password Manager. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            run();
            break;
    }
}

bool PasswordManager::checkPasswordStrength(const std::string& password) {


    if (password.length() < 8) {
        return false;
    }


    bool hasUppercase = false;
    for (char c : password) {
        if (std::isupper(c)) {
            hasUppercase = true;
            break;
        }
    }
    if (!hasUppercase) {
        return false;
    }


    bool hasLowercase = false;
    for (char c : password) {
        if (std::islower(c)) {
            hasLowercase = true;
            break;
        }
    }
    if (!hasLowercase) {
        return false;
    }


    bool hasDigit = false;
    for (char c : password) {
        if (std::isdigit(c)) {
            hasDigit = true;
            break;
        }
    }
    if (!hasDigit) {
        return false;
    }


    bool hasSpecialChar = false;
    for (char c : password) {
        if (!std::isalnum(c)) {
            hasSpecialChar = true;
            break;
        }
    }
    if (!hasSpecialChar) {
        return false;
    }


    return true;
}

bool PasswordManager::checkIfPasswordUsedBefore(const std::string& password) {

    readPasswordsFromFile();

    bool isUsedBefore = false;


    for (const PasswordEntry& entry : passwords) {
        if (entry.getPassword() == password) {
            isUsedBefore = true;
            break;
        }
    }

    return isUsedBefore;
}

std::string PasswordManager::generateRandomPassword(int length, bool includeUppercase, bool includeLowercase, bool includeSpecialChars, bool includeNumbers) {
    std::string charset;

    if (includeUppercase)
        charset += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (includeLowercase)
        charset += "abcdefghijklmnopqrstuvwxyz";
    if (includeSpecialChars)
        charset += "!@#$%^&*()_+-=[]{}|;:,.<>?";
    if (includeNumbers)
        charset += "0123456789";

    std::string password;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, charset.length() - 1);

    for (int i = 0; i < length; ++i) {
        int randomIndex = distribution(generator);
        password += charset[randomIndex];
    }

    return password;
}


void PasswordManager::searchPasswords() {
    readPasswordsFromFile();
    std::string searchTerm;
    std::cout << "Enter the search term: ";
    std::cin.ignore();
    std::getline(std::cin, searchTerm);


    std::vector<PasswordEntry> searchResults;
    for (const PasswordEntry& entry : passwords) {
        if (entry.getName().find(searchTerm) != std::string::npos ||
            entry.getCategory().find(searchTerm) != std::string::npos ||
            entry.getWebsite().find(searchTerm) != std::string::npos ||
            entry.getLogin().find(searchTerm) != std::string::npos ||
            entry.getPassword().find(searchTerm) != std::string::npos) {
            searchResults.push_back(entry);
        }
    }

    if (searchResults.empty()) {
        std::cout << "No matching passwords found." << std::endl;
    } else {
        std::cout << "Search results:" << std::endl;
        for (const PasswordEntry& entry : searchResults) {
            std::cout << "Name: " << entry.getName() << std::endl;
            std::cout << "Category: " << entry.getCategory() << std::endl;
            std::cout << "Website/Service: " << entry.getWebsite() << std::endl;
            std::cout << "Login: " << entry.getLogin() << std::endl;
            std::cout << "Password: " << entry.getPassword() << std::endl;
            std::cout << std::endl;
        }
    }
}

void PasswordManager::sortPasswords() {

    readPasswordsFromFile();

    std::cout << "Select sorting options:\n";
    std::cout << "1. Sort by name\n";
    std::cout << "2. Sort by category\n";
    std::cout << "3. Sort by name and category\n";
    std::cout << "Enter your choice: ";

    int choice;
    std::cin >> choice;


    switch (choice) {
        case 1: {
            std::string sortName;
            std::cout << "Enter the name for sorting: ";
            std::cin.ignore();
            std::getline(std::cin, sortName);

            std::vector<std::string> filteredPasswords;
            for (const PasswordEntry& entry : passwords) {
                if (entry.getName() == sortName) {
                    filteredPasswords.push_back(entry.getPassword());
                }
            }

            if (filteredPasswords.empty()) {
                std::cout << "No passwords found.\n";
            } else {
                std::cout << "Sorted Passwords:\n";
                for (const std::string& password : filteredPasswords) {
                    std::cout << "Password: " << password << '\n';
                }
            }
            break;
        }
        case 2: {
            std::string sortCategory;
            std::cout << "Enter the category for sorting: ";
            std::cin.ignore();
            std::getline(std::cin, sortCategory);

            std::vector<std::string> filteredPasswords;
            for (const PasswordEntry& entry : passwords) {
                if (entry.getCategory() == sortCategory) {
                    filteredPasswords.push_back(entry.getPassword());
                }
            }

            if (filteredPasswords.empty()) {
                std::cout << "No passwords found.\n";
            } else {
                std::cout << "Sorted Passwords:\n";
                for (const std::string& password : filteredPasswords) {
                    std::cout << "Password: " << password << '\n';
                }
            }
            break;
        }
        case 3: {
            std::string sortName, sortCategory;
            std::cout << "Enter the name for sorting: ";
            std::cin.ignore();
            std::getline(std::cin, sortName);

            std::cout << "Enter the category for sorting: ";
            std::getline(std::cin, sortCategory);

            std::vector<std::string> filteredPasswords;
            for (const PasswordEntry& entry : passwords) {
                if (entry.getName() == sortName && entry.getCategory() == sortCategory) {
                    filteredPasswords.push_back(entry.getPassword());
                }
            }

            if (filteredPasswords.empty()) {
                std::cout << "No passwords found.\n";
            } else {
                std::cout << "Sorted Passwords:\n";
                for (const std::string& password : filteredPasswords) {
                    std::cout << "Password: " << password << '\n';
                }
            }
            break;
        }
        default:
            std::cout << "Invalid choice.\n";
            break;
    }
}

void PasswordManager::addPassword() {
    std::string name;
    std::string category;
    std::string website;
    std::string login;
    std::string password;

    std::cout << "Enter the name: ";

    std::getline(std::cin, name);


    loadCategories();


    std::cout << "Available categories:" << std::endl;
    for (int i = 0; i < categories.size(); ++i) {
        std::cout << i + 1 << ". " << categories[i] << std::endl;
    }

    int categoryChoice;
    do {
        std::cout << "Select the category (enter the number): ";
        std::cin >> categoryChoice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (categoryChoice < 1 || categoryChoice > categories.size()) {
            std::cout << "Invalid category selection. Please try again." << std::endl;
        }
    } while (categoryChoice < 1 || categoryChoice > categories.size());


    category = categories[categoryChoice - 1];

    std::cout << "Enter the website/service (optional): ";
    std::getline(std::cin, website);

    std::cout << "Enter the login (optional): ";
    std::getline(std::cin, login);

    std::cout
            << "Do you want to enter your own password or generate one? (enter '1' for own password, '2' for generate): ";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 1) {
        std::cout << "Enter your password: ";
        std::getline(std::cin, password);
    } else if (choice == 2) {
        int passwordLength;
        std::cout << "Enter the number of characters for the password: ";

        std::cin >> passwordLength;

        bool includeUppercase, includeLowercase, includeSpecialChars, includeNumbers;

        std::cout << "Include uppercase letters? (enter '1' for yes, '0' for no): ";
        std::cin >> includeUppercase;

        std::cout << "Include lowercase letters? (enter '1' for yes, '0' for no): ";
        std::cin >> includeLowercase;

        std::cout << "Include numbers? (enter '1' for yes, '0' for no): ";
        std::cin >> includeNumbers;

        std::cout << "Include special characters? (enter '1' for yes, '0' for no): ";
        std::cin >> includeSpecialChars;

        password = generateRandomPassword(passwordLength, includeUppercase, includeLowercase, includeSpecialChars,
                                          includeNumbers);

    } else {
        std::cout << "Invalid choice.\n";
        return;
    }
    passwords.clear();
    PasswordEntry entry(name, password, category, website, login);
    passwords.push_back(entry);

    writePasswordsToFile();

    bool isStrong = checkPasswordStrength(password);
    bool isUsedBefore = checkIfPasswordUsedBefore(password);

    std::cout << "Password strength: " << (isStrong ? "Strong" : "Weak") << '\n';
    std::cout << "Password used before: " << (isUsedBefore ? "Yes" : "No") << '\n';
}

void PasswordManager::editPassword() {
    readPasswordsFromFile();

    if (passwords.empty()) {
        std::cout << "No passwords found. Please add passwords first." << std::endl;
        return;
    }

    std::cout << "Enter the name of the password to edit: ";
    std::string passwordName;
    std::getline(std::cin >> std::ws, passwordName);


    auto iter = std::find_if(passwords.begin(), passwords.end(), [&passwordName](const PasswordEntry& entry) {
        return entry.getName() == passwordName;
    });

    if (iter == passwords.end()) {
        std::cout << "Password '" << passwordName << "' not found." << std::endl;
        return;
    }

    std::cout << "Enter the new password: ";
    std::string newPassword;
    std::getline(std::cin >> std::ws, newPassword);


    iter->setPassword(newPassword);

    savePasswords();

    std::cout << "Password '" << passwordName << "' updated successfully." << std::endl;
}

void PasswordManager::deletePassword() {

    readPasswordsFromFile();

    std::string passwordName;
    std::cout << "Enter the name of the password you want to delete: ";
    std::getline(std::cin, passwordName);

    bool passwordFound = false;
    for (auto it = passwords.begin(); it != passwords.end(); ++it) {
        if (it->getName() == passwordName) {
            passwordFound = true;
            std::cout << "Password found: " << it->getName() << std::endl;
            std::cout << "Are you sure you want to delete this password? (y/n): ";
            std::string confirm;
            std::getline(std::cin, confirm);
            if (confirm == "y" || confirm == "Y") {
                passwords.erase(it);
                std::cout << "Password deleted successfully." << std::endl;
                savePasswords();
            } else {
                std::cout << "Deletion canceled." << std::endl;
            }
            break;
        }
    }

    if (!passwordFound) {
        std::cout << "No password with the given name was found." << std::endl;
    }
}


void PasswordManager::addCategory() {

    loadCategories();

    std::string newCategory;
    std::cout << "Enter the new category name: ";
    std::getline(std::cin, newCategory);

    for (const std::string& existingCategory : categories) {
        if (existingCategory == newCategory) {
            std::cout << "Category already exists." << std::endl;
            return;
        }
    }


    categories.push_back(newCategory);

    std::cout << "Category added successfully." << std::endl;
    saveCategories();
}

void PasswordManager::saveCategories() {
    std::ofstream outputFile("files/category-files");
    if (!outputFile) {
        std::cout << "Failed to open the category file." << std::endl;
        return;
    }

    for (const std::string& category : categories) {
        outputFile << category << '\n';
    }

    outputFile.close();
    std::cout << "Categories saved successfully." << std::endl;
}

void PasswordManager::loadCategories() {
    std::ifstream inputFile("files/category-files");
    if (!inputFile) {
        std::cout << "Category file not found. Creating a new category file." << std::endl;
        return;
    }
    categories.clear();

    std::string category;
    while (std::getline(inputFile, category)) {
        categories.push_back(category);
    }

    inputFile.close();
    std::cout << "Categories loaded successfully." << std::endl;
}

void PasswordManager::deleteCategory() {
    loadCategories();

    if (categories.empty()) {
        std::cout << "No categories found. Please add categories first." << std::endl;
        return;
    }

    std::cout << "Available categories:" << std::endl;
    for (int i = 0; i < categories.size(); ++i) {
        std::cout << i + 1 << ". " << categories[i] << std::endl;
    }

    int categoryIndex;
    std::cout << "Enter the index of the category to delete: ";
    std::cin >> categoryIndex;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (categoryIndex < 1 || categoryIndex > categories.size()) {
        std::cout << "Invalid category index. Please try again." << std::endl;
        return;
    }

    std::string categoryToDelete = categories[categoryIndex - 1];


    readPasswordsFromFile();

    auto iter = passwords.begin();
    while (iter != passwords.end()) {
        if (iter->getCategory() == categoryToDelete) {
            iter = passwords.erase(iter);
        } else {
            ++iter;
        }
    }

    categories.erase(categories.begin() + categoryIndex - 1);

    std::cout << "Category '" << categoryToDelete << "' and associated passwords have been deleted." << std::endl;

    saveCategories();
    savePasswords();
}







