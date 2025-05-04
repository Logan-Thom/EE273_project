#pragma once

#include "AdminControlls.h"
#include "Product.h"
#include "Coupon.h"
#include "Basket.h"
#include <vector>

class ECommerce {
    private:

    
        std::vector<Product> products;
        std::vector<Coupon> coupons;
        AdminControlls adminControlls{products};

    public:
        std::vector<std::pair<Product, int>> basket;

    public:
        ECommerce();
        ~ECommerce();
        std::vector<Product> LoadProductsFromFile();
        std::vector<Coupon> LoadCouponsFromFile();

};


