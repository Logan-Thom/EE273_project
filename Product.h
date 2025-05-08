#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
protected:
    std::string id;
    std::string name;
    std::string category;
    double price;
    int stock;
public:
    Product(int id, const std::string &name, const std::string &category, double price, int stock);
    
    // Display product details
    void displayProduct() const;
    void removeStock(int quantity);
    void addStock(int quantity);
    // Getters
    std::string getId() const; 
    std::string getName() const;
    std::string getCategory() const;
    double getPrice() const;
    int getStock() const;
    
    //methods
    
};

#endif
