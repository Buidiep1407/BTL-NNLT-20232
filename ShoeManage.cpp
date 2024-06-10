#include "ShoeManage.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

ShoeManager::ShoeManager() {
    loadShoes();
}

ShoeManager::~ShoeManager() {
    saveShoes();
}

void ShoeManager::loadShoes() {
    std::ifstream file("shoes.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            int id;
            std::string name, brand;
            double price;
            int quantity;
            if (iss >> id >> name >> brand >> price >> quantity) {
                shoes.push_back({id, name, brand, price, quantity});
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file shoes.txt" << std::endl;
    }
}

void ShoeManager::saveShoes() {
    std::ofstream file("shoes.txt");
    if (file.is_open()) {
        for (const auto &shoe : shoes) {
            file << shoe.id << " " << shoe.name << " " << shoe.brand << " " << shoe.price << " " << shoe.quantity << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file shoes.txt" << std::endl;
    }
}

void ShoeManager::addShoe(const std::string &name, const std::string &brand, double price, int quantity) {
    int id = shoes.empty() ? 1 : shoes.back().id + 1;
    shoes.push_back({id, name, brand, price, quantity});
}
//nếu shoe có sẵn thì??

void ShoeManager::editShoe(int id, const std::string &name, const std::string &brand, double price, int quantity) {
    for (auto &shoe : shoes) {
        if (shoe.id == id) {
            shoe.name = name;
            shoe.brand = brand;
            shoe.price = price;
            shoe.quantity = quantity;
            break;
        }
    }
}

void ShoeManager::deleteShoe(int id) {
    shoes.erase(std::remove_if(shoes.begin(), shoes.end(), [id](const Shoe &shoe) {
        return shoe.id == id;
    }), shoes.end());
}

void ShoeManager::displayShoes() {
    if (shoes.empty()) {
        std::cout << "No shoes available." << std::endl;
    } else {
        for (const auto &shoe : shoes) {
            std::cout << "ID: " << shoe.id << ", Name: " << shoe.name << ", Brand: " << shoe.brand 
                      << ", Price: " << shoe.price << ", Quantity: " << shoe.quantity << std::endl;
        }
    }
}
void ShoeManager::searchShoes(const std::string &keyword) {
    // Implement the search logic here
    for (const auto &shoe : shoes) { // Assuming `shoes` is a container of shoe objects
        if (shoe.name.find(keyword) != std::string::npos || shoe.brand.find(keyword) != std::string::npos) {
            std::cout << "Name: " << shoe.name << ", Brand: " << shoe.brand << ", Price: " << shoe.price << ", Quantity: " << shoe.quantity << std::endl;
        }
        //thêm phần không phân biệt chữ hoa, chữ thường
    }
}

