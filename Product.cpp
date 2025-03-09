#include "Product.h"
#include <iostream>
#include <iomanip>

Product::Product(int id, const std::string& name, const std::string& category, double price, int stock)
    : id(id), name(name), category(category), price(price), stock(stock) {
}

void Product::displayProduct() const {
    std::cout << "ID: " << id << " | " << name << " | " << category
        << " | " << static_cast<char>(156) << price << " | {stock: "<< stock <<"}" << std::endl;

}

// Getter functions
int Product::getId() const { return id; }
std::string Product::getName() const { return name; }
std::string Product::getCategory() const { return category; }
double Product::getPrice() const { return price; }
int Product::getStock() const { return stock; }

//methods
void Product::removeStock(int quantity) {
    stock -= quantity;
}