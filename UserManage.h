#ifndef USERMANAGE_H
#define USERMANAGE_H

#include <string>
#include <unordered_map>
#include <vector>

// Cấu trúc người dùng
struct User {
    std::string username;
    std::string password;
    std::string role;
};

// Hàm để mã hóa mật khẩu (mã hóa đơn giản)
std::string hashPassword(const std::string &password);

// Lớp quản lý người dùng
class UserManager {
    std::unordered_map<std::string, User> users;
    User *loggedInUser;

public:
    UserManager();
    ~UserManager();

    void loadUsers();
    void saveUsers();

    bool login(const std::string &username, const std::string &password);
    void logout();
    bool signup(const std::string &username, const std::string &password, const std::string &role);
    User* getLoggedInUser();
    bool isAdmin();
    
    void displayUsers();  // Thêm phương thức hiển thị danh sách người dùng
    bool deleteUser(const std::string &username);  // Thêm phương thức xóa người dùng
    bool editUser(const std::string &username, const std::string &newPassword, const std::string &newRole);  // Thêm phương thức chỉnh sửa người dùng
};

#endif
