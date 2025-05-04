#pragma once

#include "Order.h"
#include "Product.h"
#include "Coupon.h"
#include "Basket.h"
#include <vector>

class ECommerce {
    private:
        Order order;
    
        std::vector<Product> products;
        std::vector<Coupon> coupons;

    public:
        std::vector<std::pair<Product, int>> basket;

    public:
        ECommerce();
        ~ECommerce();
        std::vector<Product> LoadProductsFromFile();
        std::vector<Coupon> LoadCouponsFromFile();

};