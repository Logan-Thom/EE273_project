

#pragma once
#include "Display.h"
#include <string>
#include <vector>
#include "Product.h"

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
        float total_payment
    };

    std::Vector<productInformation> vector_of_products;
    
    bool running;


    public:
    AdminControlls(){
        this->running = true;
    }
    void displayAdminMenu();
    void menuOptionSelect();
    void viewOrderHistory();
    void viewInventory();
    void manageInventory();
    void editProductFile();
    void returnToMainMenu();

}