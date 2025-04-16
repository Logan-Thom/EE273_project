#include "Product.h"
#include <iostream>
#include <iomanip>

// Constructor
Product::Product(std::string id, const std::string& name, const std::string& category, double price, int stock)
    : id(id), name(name), category(category), price(price), stock(stock) {
}

// Virtual method - can be overridden
void Product::displayProduct() const {
    std::string idNumberOnly = id.substr(1); // Remove the first character (P)

    std::cout << std::left
        << std::setw(10) << ("ID: " + idNumberOnly)
        << std::setw(25) << name
        << std::setw(20) << category
        << std::setw(1) << static_cast<char>(156)
        << std::setw(10) << price
        << std::setw(15) << ("{stock: " + std::to_string(stock) + "}")
        << std::endl;
}

// Virtual method - can be overridden
void Product::removeStock(int quantity) {
    stock -= quantity;
}

// Virtual method - can be overridden
int Product::getStock() const {
    return stock;
}

// Getters
std::string Product::getId() const { return id; }
std::string Product::getName() const { return name; }
std::string Product::getCategory() const { return category; }
double Product::getPrice() const { return price; }
