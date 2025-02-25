#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    int id;
    std::string name;
    std::string category;
    double price;
public:
    Product(int id, const std::string &name, const std::string &category, double price);
    
    // Display product details
    void displayProduct() const;

    // Getters
    int getId() const; 
    std::string getName() const;
    std::string getCategory() const;
    double getPrice() const;
};

#endif
