#include "Database.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::shared_ptr<Product>> loadProductsFromFile() {
    std::vector<std::shared_ptr<Product>> productList;
    std::ifstream file("products.txt");

    if (!file) {
        std::cerr << "Error: Could not open file products.txt" << std::endl;
        return productList;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, name, category, priceStr, stockStr;

        if (std::getline(ss, id, ',') &&
            std::getline(ss, name, ',') &&
            std::getline(ss, category, ',') &&
            std::getline(ss, priceStr, ',') &&
            std::getline(ss, stockStr, ',')) {
            double price = std::stod(priceStr);
            int stock = std::stoi(stockStr);

            productList.push_back(std::make_shared<Product>(id, name, category, price, stock));
        }
    }

    return productList;
}



std::vector<std::shared_ptr<Product>> loadServicesFromFile() {
    std::vector<std::shared_ptr<Product>> serviceList;
    std::ifstream file("services.txt");

    if (!file) {
        std::cerr << "Error: Could not open services.txt" << std::endl;
        return serviceList;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, name, category, priceStr;

        if (std::getline(ss, id, ',') &&
            std::getline(ss, name, ',') &&
            std::getline(ss, category, ',') &&
            std::getline(ss, priceStr, ',')) {

            double price = std::stod(priceStr);
            serviceList.push_back(std::make_shared<Service>(id, name, category, price));
        }
    }

    return serviceList;
}




void addOrdertoDB(std::string timestamp, std::string maskedCardNumber, std::string expiryDate, std::string email, int couponID, const std::vector<std::pair<std::shared_ptr<Product>, int>>& basket) {
    std::ofstream orderFile("orders.txt", std::ios::app);
    if (!orderFile) {
        std::cerr << "Error: Could not open orders.txt to save the order.\n";
        return;
    }

    orderFile << timestamp << ","
        << maskedCardNumber << ","
        << expiryDate << ","
        << email << ","
        << couponID << ",";

    for (const auto& item : basket) {
        orderFile << item.first->getId() << "," << item.second << ",";
    }

    orderFile << 0 << "\n";
}



// =================== COUPON MANAGEMENT ===================

// Load all coupons from file
std::vector<Coupon> loadCouponsFromFile() {
    std::vector<Coupon> coupons;
    std::ifstream file("coupons.txt");

    if (!file) {
        std::cerr << "Error: Unable to open file " << "coupons.txt" << std::endl;
        return coupons;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, code, discountStr, usedStr, maxUsesStr, activeStr;

        if (std::getline(ss, idStr, ',') &&
            std::getline(ss, code, ',') &&
            std::getline(ss, discountStr, ',') &&
            std::getline(ss, usedStr, ',') &&
            std::getline(ss, maxUsesStr, ',') &&
            std::getline(ss, activeStr)) {

            int id = std::stoi(idStr);
            double discount = std::stod(discountStr); 
            int used = std::stoi(usedStr);
            int maxUses = std::stoi(maxUsesStr);
            bool active = (std::stoi(activeStr) == 1);

            coupons.emplace_back(id, code, discount, maxUses, used, active);
        }
    }

    file.close();
    return coupons;
}
void updateCouponUsage(int couponID, std::vector<Coupon>& coupons){
   
    for (auto& coupon : coupons) {
        if (coupon.getCouponID() == couponID) {
            coupon.usesCoupon();
            break;
        }
    }

    std::ofstream outFile("coupons.txt");
    if (!outFile) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;
    }

    for (const auto& coupon : coupons) {
        outFile << coupon.getCouponID() << "," << coupon.getCode() << ","
            << coupon.getDiscountPercentage() << "," << coupon.getUsed() << ","
            << coupon.getMaxUses() << "," << coupon.isActive() << "\n";
    }

    outFile.close();
    return;
}


void checkoutUpdateStock(const std::vector<std::pair<std::shared_ptr<Product>, int>>& basket) {
    std::vector<std::shared_ptr<Product>> products = loadProductsFromFile();

    for (const auto& item : basket) {
        for (auto& product : products) {
            if (product->getId() == item.first->getId()) {
                product->removeStock(item.second);
            }
        }
    }

    std::ofstream outFile("products.txt");
    if (!outFile) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;
    }

    for (const auto& product : products) {
        outFile << product->getId() << "," << product->getName() << ","
            << product->getCategory() << "," << product->getPrice() << ","
            << product->getStock() << "\n";
    }
}

