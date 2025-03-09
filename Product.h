#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    int id;
    std::string name;
    std::string category;
    double price;
    int stock;
public:
    Product(int id, const std::string &name, const std::string &category, double price, int stock);
    
    // Display product details
    void displayProduct() const;

    // Getters
    int getId() const; 
    std::string getName() const;
    std::string getCategory() const;
    double getPrice() const;
    int getStock() const;
};

#endif
