/*
Implementation of Product class
Created for: EE273 E-Commerce Project
Last Updated: 08/05/25
Updated By: Logan Thom, Jamie Briggs
*/
#include "Product.h"
#include <string>
#include <iostream>
#include <iomanip>

Product::Product(std::string id, const std::string& name, const std::string& category, double price, int stock)
    : id(id), name(name), category(category), price(price), stock(stock) {
}

void Product::displayProduct() const {
    std::cout << "ID: " << id << " | " << name << " | " << category
        << " | " << static_cast<char>(156) << price << " | {stock: "<< stock <<"}" << std::endl;

}

void Product::addStock(int quantity){
    this->stock += quantity;
}

// Getter functions
std::string Product::getId() const { return id; }
std::string Product::getName() const { return name; }
std::string Product::getCategory() const { return category; }
double Product::getPrice() const { return price; }
int Product::getStock() const { return stock; }

//methods
void Product::removeStock(int quantity) {
    stock -= quantity;
}