#include "Database.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Product> loadProductsFromFile() {
    std::vector<Product> productList;
    std::ifstream file("products.txt");

    if (!file) {
        std::cerr << "Error: Could not open file " << "products.txt" << std::endl;
        return productList;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name, category, priceStr, stockStr;

        // Read comma-separated values
        if (std::getline(ss, idStr, ',') &&
            std::getline(ss, name, ',') &&
            std::getline(ss, category, ',') &&
            std::getline(ss, priceStr, ',') &&
            std::getline(ss, stockStr, ',')) {
            int id = std::stoi(idStr);
            double price = std::stod(priceStr);
            int stock = std::stoi(stockStr);

            productList.emplace_back(id, name, category, price, stock);
        }
    }

    file.close();
    return productList;
}



void addOrdertoDB(std::string timestamp, std::string maskedCardNumber, std::string expiryDate, std::string email, int couponID, std::vector<std::pair<Product, int>>& basket) {
    // Save order details to file (ADD to DATAbase.cpp)
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
        orderFile << item.first.getId() << "," << item.second << ",";
    }

    orderFile <<0<< "\n";

    orderFile.close();
    return;
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


void checkoutUpdateStock(std::vector<std::pair<Product, int>>& basket) {
    std::vector<Product> products = loadProductsFromFile();

    for (const auto& item : basket) {
        for (auto& product : products) {
            if (product.getId() == item.first.getId()) {
                product.removeStock(item.second);
            }
        }
    }

    std::ofstream outFile("products.txt");
    if (!outFile) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;
    }
    for (const auto& product : products) {
        outFile << product.getId() << "," << product.getName() << ","
            << product.getCategory() << "," << product.getPrice() << ","
            << product.getStock() << "\n";
    }

    outFile.close();
    return;

}
