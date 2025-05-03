#pragma once

#include "Order.h"
#include "Product.h"
#include "Coupon.h"
#include <vector>

class ECommerce {
    private:
        Order order;
    
        std::vector<Product> products;
        std::vector<Coupon> coupons;
    public:
        ECommerce();
        ~ECommerce();
        std::vector<Product> LoadProductsFromFile();
        std::vector<Coupon> LoadCouponsFromFile();

};