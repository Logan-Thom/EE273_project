#pragma once

#include "AdminControlls.h"
#include "Product.h"
#include "Coupon.h"
#include "Basket.h"
#include "Database.h"
#include "Display.h"
#include <vector>
#include <utility> // For std::pair

class ECommerce : public Display {
    private:


        std::vector<Product> products;
        std::vector<Coupon> coupons;
        AdminControlls adminControlls{products};

    public:
        Basket basket_utils;
        Database database_utils;
        std::vector<std::pair<Product, int>> basket;

    public:
        ECommerce();
        ~ECommerce();
        void LoadProducts(void);
        void LoadCoupons(void);
        AdminControlls GetAdminControlls(void);
        //menu related
        int getTotalBasketItems(const std::vector<std::pair<Product, int>>& basket);
        void displayMainMenu(const std::vector<std::pair<Product, int>>& basket);
        void handleMenuSelection(void);
        void browseProducts(std::vector<std::pair<Product, int>>& basket);
        void attemptLogin(void);
};


