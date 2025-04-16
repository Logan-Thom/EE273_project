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
    Product(std::string id, const std::string& name, const std::string& category, double price, int stock);

    // Virtual methods for polymorphism
    virtual void displayProduct() const;
    virtual void removeStock(int quantity);
    virtual int getStock() const;

    // Getters
    std::string getId() const;
    std::string getName() const;
    std::string getCategory() const;
    double getPrice() const;

    // Virtual destructor (best practice when using inheritance)
    virtual ~Product() = default;
};

#endif
