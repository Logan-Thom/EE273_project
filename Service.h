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