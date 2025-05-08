#pragma once

#include "AdminControlls.h"
#include "Product.h"
#include "Coupon.h"
#include "Checkout.h"
#include "Basket.h"
#include "Service.h"
#include "Database.h"
#include "Display.h"
#include <vector>
#include <utility> // For std::pair

class Basket;
class Checkout;


class ECommerce : public Display {
    private:
        std::vector<Product> products;
        std::vector<Coupon> coupons;
        std::vector<Product> services;
        AdminControlls adminControlls{products};

    public:
        Basket* basket_utils;
        Database* database_utils; //these need to be pointers because of circular and forward declarations (ECommerce uses Database, database uses reference of Ecommerce)
        Checkout* checkout_utils;
        Service* service_utils;
        std::vector<std::pair<Product, int>> basket;

    public:
        ECommerce();
        ~ECommerce();
        void LoadProducts(void);
        void LoadCoupons(void);
        void LoadServices(void);
        //getters
        AdminControlls GetAdminControlls(void);
        std::vector<Coupon> GetCoupons(void);
        //menu related
        int getTotalBasketItems(const std::vector<std::pair<Product, int>>& basket);
        void displayMainMenu(const std::vector<std::pair<Product, int>>& basket);
        void handleMenuSelection(void);
        void browseProducts(std::vector<std::pair<Product, int>>& basket);
        void attemptLogin(void);
};