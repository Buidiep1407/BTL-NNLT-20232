#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include "UserManage.h"

using namespace std;

// Hàm để mã hóa mật khẩu (mã hóa đơn giản)
string hashPassword(const string &password) {
    string hashed = password; // Dummy hash
    reverse(hashed.begin(), hashed.end());
    return hashed;
}

// Khởi tạo đối tượng UserManager và tải dữ liệu người dùng từ file
UserManager::UserManager() : loggedInUser(nullptr) {
    loadUsers();
}

// Hủy đối tượng UserManager và lưu dữ liệu người dùng vào file
UserManager::~UserManager() {
    saveUsers();
}

// Tải dữ liệu người dùng từ file
void UserManager::loadUsers() {
    ifstream file("users.txt");
    if (file.is_open()) {
        string username, password, role;
        while (file >> username >> password >> role) {
            users[username] = {username, password, role};
        }
        file.close();
    }
}

// Lưu dữ liệu người dùng vào file
void UserManager::saveUsers() {
    ofstream file("users.txt");
    if (file.is_open()) {
        for (const auto &pair : users) {
            const User &user = pair.second;
            file << user.username << " " << user.password << " " << user.role << endl;
        }
        file.close();
    }
}

// Đăng nhập
bool UserManager::login(const string &username, const string &password) {
    auto it = users.find(username);
    if (it != users.end() && it->second.password == hashPassword(password)) {
        loggedInUser = &it->second;
        return true;
    }
    return false;
}

// Đăng xuất
void UserManager::logout() {
    loggedInUser = nullptr;
}

// Đăng ký
bool UserManager::signup(const string &username, const string &password, const string &role) {
    if (users.find(username) == users.end()) {
        users[username] = {username, hashPassword(password), role};
        return true;
    }
    return false;
}
//nếu user có sẵn thì ???


// Lấy thông tin người dùng đã đăng nhập
User* UserManager::getLoggedInUser() {
    return loggedInUser;
}

// Kiểm tra vai trò người dùng
bool UserManager::isAdmin() {
    return loggedInUser && loggedInUser->role == "admin";
}

// Hiển thị danh sách người dùng
void UserManager::displayUsers() {
    for (const auto &pair : users) {
        const User &user = pair.second;
        cout << "Username: " << user.username << ", Role: " << user.role << endl;
    }
}

// Xóa người dùng
bool UserManager::deleteUser(const string &username) {
    auto it = users.find(username);
    if (it != users.end()) {
        users.erase(it);
        return true;
    }
    return false;
}

// Chỉnh sửa người dùng
bool UserManager::editUser(const string &username, const string &newPassword, const string &newRole) {
    auto it = users.find(username);
    if (it != users.end()) {
        it->second.password = hashPassword(newPassword);
        it->second.role = newRole;
        return true;
    }
    return false;
}
