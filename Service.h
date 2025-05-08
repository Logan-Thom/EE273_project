/*
Child class of products, having all of the same functionality but reduced access to stock values. 
Created for: EE273 E-Commerce Project
Last Updated: 08/05/25
Updated By: Logan Thom, Jamie Briggs
*/

#ifndef SERVICE_H
#define SERVICE_H

#include "Product.h"

class Service : public Product {
public:
    // Constructor (no stock input; fixed to 1)
    Service(const std::string& id, const std::string& name, const std::string& category, double price);

    // Overrides
    void displayProduct() const override;
    int getStock() const override;
    void removeStock(int quantity) override;
};

#endif