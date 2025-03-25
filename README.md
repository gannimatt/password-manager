# Password Manager Project

## Description
This Password Manager is a C++ console-based application that securely stores, manages, and generates passwords. It allows users to organize passwords into categories, ensuring easier management and retrieval.

## Features
- **Password Storage:** Store multiple passwords with details such as category, website, and login.
- **Password Generation:** Automatically generate secure passwords with customizable complexity.
- **Password Strength Validation:** Verify password strength based on defined criteria.
- **Search and Sorting:** Easily search and sort passwords by name, category, or both.
- **Category Management:** Add, view, and delete custom categories for better organization.

## File Structure
- `main.cpp`: Application entry point, initializes and launches the Password Manager.
- `PasswordManager.cpp/.h`: Implements core functionality like password operations, category management, and file operations.
- `PasswordEntry.cpp/.h`: Defines the data structure for individual password entries.

## Usage

### Running the Application
Compile and run the program using:
```bash
g++ main.cpp PasswordManager.cpp PasswordEntry.cpp -o PasswordManager
./PasswordManager
```

### Menu Options
1. **Search Passwords**: Search stored passwords based on various criteria.
2. **Sort Passwords**: Sort passwords by name, category, or both.
3. **Add Password**: Add new passwords either manually or via automated generation.
4. **Edit Password**: Update existing password entries.
5. **Delete Password**: Remove passwords from storage.
6. **Add Category**: Introduce new categories.
7. **Delete Category**: Delete existing categories along with their associated passwords.
0. **Exit**: Close the application.

## Password Strength Criteria
Passwords must meet the following to be considered strong:
- Minimum of 8 characters.
- At least one uppercase and one lowercase letter.
- At least one digit.
- At least one special character.

## Data Storage
Passwords and categories are stored in files within the application's directory:
- **Passwords:** `files/password-files/password.txt` or `password2.txt`
- **Categories:** `files/category-files`

## Dependencies
- C++17 (due to filesystem usage)

## Contributions
Contributions are welcome! Feel free to fork, submit issues, and send pull requests to enhance the project.

## License
This project is open-source and available for modification and reuse.
