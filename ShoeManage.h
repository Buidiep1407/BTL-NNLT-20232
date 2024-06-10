#ifndef SHOEMANAGE_H
#define SHOEMANAGE_H

#include <vector>
#include <string>

// Cấu trúc sản phẩm giày dép
struct Shoe {
    int id;
    std::string name;
    std::string brand;
    double price;
    int quantity;
};

// Lớp quản lý giày dép
class ShoeManager {
    std::vector<Shoe> shoes;

public:
    ShoeManager();
    ~ShoeManager();

    void loadShoes();
    void saveShoes();
    void addShoe(const std::string &name, const std::string &brand, double price, int quantity);
    void editShoe(int id, const std::string &name, const std::string &brand, double price, int quantity);
    void deleteShoe(int id);
    void displayShoes();
    void searchShoes(const std::string &keyword);
};

#endif
