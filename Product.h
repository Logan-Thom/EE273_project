/*
Class Header for storage of product data types and handling of that data
Created for: EE273 E-Commerce Project
Last Updated: 08/05/25
Updated By: Logan Thom, Jamie Briggs
*/

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
    Product(std::string id, const std::string &name, const std::string &category, double price, int stock);
    
    // Display product details
    virtual void displayProduct() const;
    virtual void removeStock(int quantity);
    void addStock(int quantity);
    // Getters
    std::string getId() const; 
    std::string getName() const;
    std::string getCategory() const;
    double getPrice() const;
    virtual int getStock() const;
    
    //methods
    
};

#endif
