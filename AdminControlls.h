#pragma once
#include "Display.h"
#include <string>
#include <vector>
#include "Product.h"
#include "Coupon.h"
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
        int items_bought; //may be able to use this to combine orders within the vector
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
        std::vector<Product> products_vec;
        std::vector<Product> services_vec;
        std::vector<Coupon> coupons_vec;

    public:
    AdminControlls(std::vector<Product>& prod, std::vector<Product>& serv, std::vector<Coupon>& coup){
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