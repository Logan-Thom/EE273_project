/*
Class Header containing functionality for admin menu controlls and options
Created for: EE273 E-Commerce Project
Last Updated: 08/05/25
Updated By: Logan Thom, Jamie Briggs
*/

#pragma once
#include "Display.h"
#include <string>
#include <vector>
#include "Product.h"
#include "Coupon.h"
#include <memory>
#include "Order.h"

class AdminControlls : public Display {
    private:

    struct productInformation{
        int id;
        std::string product_name;
        float price;
        int stock;
    };

    struct orderInformation{
        int items_bought; //able to use this to combine orders within the vector
        std::string date;
        std::string time;
        int card_identifier;
        std::string stock;
        std::string item;
        int quantity;
        float unit_cost;
        float total_payment;
    };

    //std::vector<productInformation> vector_of_products;
    
    public:
        Order order;
        std::vector<std::shared_ptr<Product>> products_vec;
        std::vector<std::shared_ptr<Product>> services_vec;
        std::vector<Coupon> coupons_vec;

    public:
    AdminControlls(std::vector<std::shared_ptr<Product>>& prod, std::vector<std::shared_ptr<Product>>& serv, std::vector<Coupon>& coup){
        this->products_vec = prod;
        this->services_vec = serv;
        this->coupons_vec = coup;
    }
    void displayAdminMenu();
    void menuOptionSelect();
    void viewInventory();
    void viewProducts();
    void manageInventory();
    void manageCoupons();
    void editProductVec();
    bool returnToMainMenu();
    void DisplayCoupons();
};