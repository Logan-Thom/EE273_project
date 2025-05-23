/*
Implementation of AdminControlls class
Created for: EE273 E-Commerce Project
Last Updated: 08/05/25
Updated By: Logan Thom, Jamie Briggs
*/
#include "AdminControlls.h"
#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>


void AdminControlls::displayAdminMenu(){
    RefreshScreen(); //inherited method from Display class
    
    std::cout << "1. View Inventory" << std::endl;
    std::cout << "2. Manage Inventory" << std::endl;
    std::cout << "3. View Order History" << std::endl;
    std::cout << "4. Mange Coupons" << std::endl;
    std::cout << "5. Add Product" << std::endl;
    std::cout << "6. Return to Main Menu" << std::endl;
    std::cout << "========================\n";
}

//may be able to use this as inheritted with menu, operator overloaded 
//to select the correct one, talk to Jamie about it
void AdminControlls::menuOptionSelect(){

bool running = true;
    while(running){
        this->displayAdminMenu();

        //this can also be inheritted
        int choice = 0;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > 6) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Returning...\n";
            PauseProgram();
            return;
        }


        switch(choice){
            case 1:
                this->viewInventory();
                this->PauseProgram(); //keep on screen until input
                break;
            case 2:
                this->manageInventory();
                break;
            case 3:
                this->order.SortDataVec(); //make sure everything is okay first
                this->order.OrderViewSelect();
                break;
            case 4:
                this->manageCoupons();
                break;
            case 5:
                //add product
                this->addProduct();
                break;
            case 6:
                running = this->returnToMainMenu();
                break;
            default:
                std::cout << "Unknown option, returning to main menu..." << std::endl;
                this->returnToMainMenu();
                break; //probably don't need to break on default
        }
    }
}




//lord help me
void AdminControlls::viewInventory(){
    //take the products
    //how do I do this?
    this->viewProducts(); //no repeating

    for (auto& serv : this->services_vec){
        std::cout << serv->getId() << " " << serv->getName() << std::endl;
    }

}

void AdminControlls::addProduct(){
    std::string new_name;
    std::cout << "Enter the name of the product" << std::endl;
    std::cin >> new_name;

    std::string new_cat;
    std::cout << "Enter the category of the new product (P) or (S)" << std::endl;
    std::cin >> new_cat;

    float new_price;
    std::cout << "Enter the price of the new product" << std::endl;
    std::cin >> new_price;

    int n_stock;
    std::cout << "How much stock is available?" << std::endl;
    std::cin >> n_stock;

    std::string category_ps;
    if(new_cat == "P"){
        category_ps = "Product";
        this->products_vec.push_back(std::make_shared<Product>((new_cat + std::to_string((products_vec.size())+1)), new_name, category_ps, new_price, n_stock));
    } else if(new_cat == "S") {
        category_ps = "Service";
        this->services_vec.push_back(std::make_shared<Service>((new_cat + std::to_string((products_vec.size())+1)), new_name, category_ps, new_price, n_stock));
    }

    
}

void AdminControlls::viewProducts(){
    for (auto& prod : this->products_vec){
        std::cout << prod->getId() << " " << prod->getName() << " " << prod->getStock() << std::endl;
    }
}


void AdminControlls::manageInventory(){
    //view so you can actually see what is being editted, 
    bool stay_on_screen = true;
    while(stay_on_screen){
        //should refresh inventory view each time
        this->viewProducts();

        std::string ID_for_restock;
        int num_to_restock;
        std::cout << "Select number of ID of item to restock, 'back' to return" << std::endl;
        std::cin >> ID_for_restock;
        int ID;


        if (ID_for_restock == "back"){
            stay_on_screen = false;
            return;
        } else {
            ID = stoi(ID_for_restock);
        }

        //this may not work, need to check reference
        std::cout << "How many items do you wish to add? " << std::endl;
        std::cin >> num_to_restock;
        products_vec[ID - 1]->addStock(num_to_restock);
    }
}

//this could maybe be a virtual/overriden function, look into it, at the least it can inherrit
//Note: no longer needed
/*
void AdminControlls::editProductVec(){
    //open file for write, and write contents of vector to it.
    //this wouldn't need to exist if previous files were better
    std::ofstream productFile("products.txt");

    for(int i=0; i<products_vec.size();i++){
        productFile << products_vec[i].getId() << "," << products_vec[i].getName() << "," << products_vec[i].getPrice() << "," << products_vec[i].getStock();
    }

    productFile.close();
}
*/
bool AdminControlls::returnToMainMenu(){
    //in case extra things need to be done here
    return false;
}

void AdminControlls::manageCoupons(){
    //do this
    int choice;
    int coupon_id;
    while(true){
        RefreshScreen();
        std::cout << "1. Add Coupon" << std::endl;
        std::cout << "2. Adjust Coupon" << std::endl;
        std::cout << "3. Delete Coupon" << std::endl;
        std::cout << "4. Return" << std::endl;
        std::cout << "========================" << std::endl;

        std::cin >> choice;
        switch(choice){
            case 1: {
                std::cout << "Name of coupon: " << std::endl;
                std::string new_name;
                std::cin >> new_name;

                std::cout << "Discount (decimal): " << std::endl;
                double new_discount;
                std::cin >> new_discount;

                std::cout << "Maximum uses: " << std::endl;
                int new_muses;
                std::cin >> new_muses;

                coupons_vec.push_back(Coupon((coupons_vec.back().getCouponID() + 1), new_name, new_discount, new_muses));
                break;

            }
            case 2: {
                this->DisplayCoupons();
                std::cout << "Enter ID of coupon to alter" << std::endl;
                std::cin >> coupon_id;
                std::cout << "(1) Change Discount, (2) Change Uses." << std::endl;
                int option;
                std::cin >> option;
                if(option == 1){
                    std::cout << "Enter new percentage as decimal" << std::endl;
                    float new_disc;
                    std::cin >> new_disc;
                    coupons_vec[coupon_id - 1].SetDiscount(new_disc);
                } else if (option == 2){
                    std::cout << "Enter new number of uses." << std::endl;
                    int newUses;
                    std::cin >> newUses;
                    coupons_vec[coupon_id - 1].SetUses(newUses);
                }
                break;
            }
            case 3: {
                this->DisplayCoupons();
                std::cout << "Enter ID of coupon to delete" << std::endl;
                std::cin >> coupon_id;
                coupons_vec[coupon_id - 1].SetActive(false);
                coupons_vec[coupon_id - 1].SetUses(0);
                break;
            }
            case 4:
                return;
            default:
                std::cout << "Invalid option." << std::endl;
                PauseProgram();
                break;
        }
    }
}

void AdminControlls::DisplayCoupons(){
    for (auto& coup : coupons_vec){
        std::cout << coup.getCouponID() << ": " << coup.getCode() << " for " << coup.getDiscountPercentage() << " off with " << coup.getMaxUses() <<" remaining uses." << std::endl;
    }
}