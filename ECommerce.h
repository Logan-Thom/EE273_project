/*
Primary Class, handles initialisation of data, intitial menus and is the entry for all functionality
Created for: EE273 E-Commerce Project
Last Updated: 08/05/25
Updated By: Logan Thom, Jamie Briggs
*/


#pragma once

#include "AdminControlls.h"
#include "Product.h"
#include "Coupon.h"
#include "Checkout.h"
#include "Basket.h"
#include "Service.h"
#include <memory>
#include "Database.h"
#include "Display.h"
#include <vector>
#include <utility> // For std::pair

class Basket;
class Checkout;
class Database;

class ECommerce : public Display {
    private:
        std::vector<std::shared_ptr<Product>> products;
        std::vector<Coupon> coupons;
        std::vector<std::shared_ptr<Product>> services;
        AdminControlls adminControlls;

    public:
        Basket* basket_utils;
        Database* database_utils; //these need to be pointers because of circular and forward declarations (ECommerce uses Database, database uses reference of Ecommerce)
        Checkout* checkout_utils;
        Service* service_utils;
        std::vector<std::pair<std::shared_ptr<Product>, int>> basket;

    public:
        ECommerce();
        ~ECommerce();
        std::vector<std::shared_ptr<Product>> LoadProducts(void);
        std::vector<Coupon> LoadCoupons(void);
        std::vector<std::shared_ptr<Product>> LoadServices(void);
        //getters
        AdminControlls& GetAdminControlls(void);
        std::vector<Coupon> GetCoupons(void);
        //menu related
        int getTotalBasketItems(const std::vector<std::pair<std::shared_ptr<Product>, int>>& basket);
        void displayMainMenu(const std::vector<std::pair<std::shared_ptr<Product>, int>>& basket);
        void handleMenuSelection(void);
        void browseProducts(std::vector<std::pair<std::shared_ptr<Product>, int>>& basket);
        void browseItems(const std::vector<std::shared_ptr<Product>>& items,std::vector<std::pair<std::shared_ptr<Product>, int>>& basket,const std::string& label,const std::string& mode);
        void attemptLogin(void);
};