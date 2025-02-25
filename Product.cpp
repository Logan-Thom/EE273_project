#include "Product.h"
#include <iostream>
#include <iomanip>

Product::Product(int id, const std::string& name, const std::string& category, double price)
    : id(id), name(name), category(category), price(price) {
}

void Product::displayProduct() const {
    std::cout << "ID: " << id << " | " << name << " | " << category
        << " | £" << std::fixed << std::setprecision(2) << price << std::endl;
}

// Getter functions
int Product::getId() const { return id; }
std::string Product::getName() const { return name; }
std::string Product::getCategory() const { return category; }
double Product::getPrice() const { return price; }
