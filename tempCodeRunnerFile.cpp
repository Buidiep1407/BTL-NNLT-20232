#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <cstdlib>
#include "UserManage.h"
#include "ShoeManage.h"

using namespace std;

// Hàm menu chính cho admin
void displayAdminMenu() {
    cout << "--------------------------------------\n";
    cout << "1. User Management\n";
    cout << "2. Shoes Management\n";
    cout << "3. Logout\n";
    cout << "Enter your choice: ";
}

// Hàm menu chính cho user
void displayUserMenu() {
    cout << "--------------------------------------\n";
    cout << "1. Shoes\n";
    cout << "2. Logout\n";
    cout << "Enter your choice: ";
}

// Menu đăng nhập ban đầu
void displayInitialMenu() {
    cout << "--------------------------------------\n";
    cout << "1. Login\n";
    cout << "2. Signup\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}

void userManagementMenu() {
    cout << "1. Display Users\n";
    cout << "2. Delete User\n";
    cout << "3. Edit User\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

void shoesManagementMenu() {
    cout << "1. Add Shoe\n";
    cout << "2. Edit Shoe\n";
    cout << "3. Delete Shoe\n";
    cout << "4. Display Shoes\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

void shoesUserMenu() {
    cout << "1. Display Shoes\n";
    cout << "2. Search Shoes\n";
    cout << "3. Back\n";
    cout << "Enter your choice: ";
}

void handleUserManagement(UserManager &userManager) {
    int userChoice;
    while (true) {
        userManagementMenu();
        cin >> userChoice;
        switch (userChoice) {
            case 1: {
                userManager.displayUsers();
                break;
            }
            case 2: {
                string username;
                cout << "Enter username to delete: ";
                cin >> username;
                if (userManager.deleteUser(username)) {
                    cout << "User deleted successfully!" << endl;
                } else {
                    cout << "User not found!" << endl;
                }
                break;
            }
            case 3: {
                string username, newPassword, newRole;
                cout << "Enter username to edit: ";
                cin >> username;
                cout << "Enter new password: ";
                cin >> newPassword;
                cout << "Enter new role (admin/user): ";
                cin >> newRole;
                if (userManager.editUser(username, newPassword, newRole)) {
                    cout << "User edited successfully!" << endl;
                } else {
                    cout << "User not found!" << endl;
                }
                break;
            }
            case 4:
                return; // Exit to the previous menu
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    }
}

void handleShoesManagement(ShoeManager &shoeManager) {
    int shoeChoice;
    while (true) {
        shoesManagementMenu();
        cin >> shoeChoice;
        switch (shoeChoice) {
            case 1: {
                string name, brand;
                double price;
                int quantity;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter brand: ";
                cin >> brand;
                cout << "Enter price: ";
                cin >> price;
                cout << "Enter quantity: ";
                cin >> quantity;
                shoeManager.addShoe(name, brand, price, quantity);
                cout << "Shoe added successfully!" << endl;
                break;
            }
            case 2: {
                int id;
                string name, brand;
                double price;
                int quantity;
                cout << "Enter shoe ID: ";
                cin >> id;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter brand: ";
                cin >> brand;
                cout << "Enter price: ";
                cin >> price;
                cout << "Enter quantity: ";
                cin >> quantity;
                shoeManager.editShoe(id, name, brand, price, quantity);
                cout << "Shoe edited successfully!" << endl;
                break;
            }
            case 3: {
                int id;
                cout << "Enter shoe ID: ";
                cin >> id;
                shoeManager.deleteShoe(id);
                cout << "Shoe deleted successfully!" << endl;
                break;
            }
            case 4: {
                shoeManager.displayShoes();
                break;
            }
            case 5:
                return; // Exit to the previous menu
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    }
}

void handleShoesUserMenu(ShoeManager &shoeManager) {
    int choice;
    while (true) {
        shoesUserMenu();
        cin >> choice;
        switch (choice) {
            case 1: {
                shoeManager.displayShoes();
                break;
            }
            case 2: {
                string name;
                cout << "Enter shoe name to search: ";
                cin >> name;
                shoeManager.searchShoes(name); // Correct function call
                break;
            }
            case 3:
                return; // Exit to the previous menu
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    }
}

void handleUserChoice(ShoeManager &shoeManager) {
    int choice;
    while (true) {
        displayUserMenu();
        cin >> choice;
        switch (choice) {
            case 1: {
                handleShoesUserMenu(shoeManager);
                break;
            }
            case 2:
                cout << "Logged out!" << endl;
                return; // Exit to the main menu
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    }
}

int main() {
    UserManager userManager;
    ShoeManager shoeManager;
    int choice;

    while (true) {
        displayInitialMenu();
        cin >> choice;

        switch (choice) {
            case 1: { // Login
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                if (userManager.login(username, password)) {
                    cout << "Login successful!" << endl;
                    bool isAdmin = userManager.isAdmin();
                    if (isAdmin) {
                        while (true) {
                            displayAdminMenu();
                            cin >> choice;
                            switch (choice) {
                                case 1:
                                    handleUserManagement(userManager);
                                    break;
                                case 2:
                                    handleShoesManagement(shoeManager);
                                    break;
                                case 3:
                                    userManager.logout();
                                    cout << "Logged out!" << endl;
                                    break;
                                default:
                                    cout << "Invalid choice! Please try again." << endl;
                                    break;
                            }
                            if (choice == 3) break; // Logout and exit the admin menu loop
                        }
                    } else {
                        while (true) {
                            displayUserMenu();
                            cin >> choice;
                            switch (choice) {
                                case 1:
                                    handleShoesUserMenu(shoeManager);
                                    break;
                                case 2:
                                    userManager.logout();
                                    cout << "Logged out!" << endl;
                                    break;
                                default:
                                    cout << "Invalid choice! Please try again." << endl;
                                    break;
                            }
                            if (choice == 2) break; // Logout and exit the user menu loop
                        }
                    }
                } else {
                    cout << "Invalid credentials!" << endl;
                }
                break;
            }
            case 2: { // Signup
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                string role = "user"; // Default role is user
                if (userManager.signup(username, password, role)) {
                    cout << "Signup as user successful!" << endl;
                } else {
                    cout << "Username already exists!" << endl;
                }
                break;
            }
            case 3:
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    }

    return 0;
}
