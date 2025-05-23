/*
Implementation of Database class
Created for: EE273 E-Commerce Project
Last Updated: 08/05/25
Updated By: Logan Thom, Jamie Briggs
*/
#include "Database.h"
#include "ECommerce.h"
#include "Service.h"
#include <fstream>
#include <memory>
#include <sstream>
#include <iostream>

std::vector<std::shared_ptr<Product>> Database::loadProductsFromFile() {
    std::vector<std::shared_ptr<Product>> productList;
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
            std::string id = idStr;
            double price = std::stod(priceStr);
            int stock = std::stoi(stockStr);

            productList.emplace_back(std::make_shared<Product>(id, name, category, price, stock));
        }
    }

    file.close();
    return productList;
}

std::vector<std::shared_ptr<Product>> Database::loadServicesFromFile(){
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

// =================== COUPON MANAGEMENT ===================

// Load all coupons from file
std::vector<Coupon> Database::loadCouponsFromFile() {
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
            bool active = 1;

            coupons.emplace_back(id, code, discount, maxUses, used, active);
        }
    }

    file.close();
    return coupons;
}
void Database::updateCouponUsage(int couponID, std::vector<Coupon>& coupons){
   
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


void Database::checkoutUpdateStock(std::vector<std::pair<std::shared_ptr<Product>, int>>& basket) {
    std::vector<shared_ptr<Product>> products = loadProductsFromFile();

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

    outFile.close();
    return;

}

void Database::save_coupons(ECommerce& ecommerce){
    ofstream coupFile("coupons.txt");
    for (auto& coup : ecommerce.GetCoupons()){
        coupFile << coup.getCouponID() << "," << coup.getCode() << "," << coup.getDiscountPercentage() << "," << coup.getUsed() << "," << coup.getMaxUses() << "," << coup.isActive() << "\n";
    }
    coupFile.close();
}