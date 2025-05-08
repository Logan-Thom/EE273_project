#include "Service.h"
#include <iostream>

#include <iomanip>  // For setw, left, right

// Always fixed stock of 1 for services
Service::Service(const std::string& id, const std::string& name, const std::string& category, double price)
    : Product(id, name, category, price, 1) {
}



void Service::displayProduct() const {
    std::string idNumber = getId().substr(1); // Remove the 'S' prefix

    std::cout << std::left
        << std::setw(10) << ("ID: " + idNumber)
        << std::setw(25) << getName()
        << std::setw(20) << getCategory()
        << std::setw(1) << static_cast<char>(156)
        << std::setw(10) << price
        << std::endl;
}


int Service::getStock() const {
    return 1; // Always available
}

void Service::removeStock(int quantity) {
    // Do nothing — service stock isn't reduced
}