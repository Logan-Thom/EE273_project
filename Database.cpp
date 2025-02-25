#include "Database.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Product> loadProductsFromFile(const std::string& filename) {
    std::vector<Product> productList;
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return productList;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name, category, priceStr;

        // Read comma-separated values
        if (std::getline(ss, idStr, ',') &&
            std::getline(ss, name, ',') &&
            std::getline(ss, category, ',') &&
            std::getline(ss, priceStr, ',')) {

            int id = std::stoi(idStr);
            double price = std::stod(priceStr);

            productList.emplace_back(id, name, category, price);
        }
    }

    file.close();
    return productList;
}
