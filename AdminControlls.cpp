#include "AdminControlls.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>


void AdminControlls::displayAdminMenu(){
    this->RefreshScreen(); //inherited method from Display class
    
    std::cout << "1. View Inventory" << std::endl;
    std::cout << "2. Manage Inventory" << std::endl;
    std::cout << "3. View Order History" << std::endl;
    std::cout << "4. Mange Coupons" << std::endl;
    std::cout << "5. Return to Main Menu" << std::endl;
    std::cout << "========================\n";
}

//may be able to use this as inheritted with menu, operator overloaded 
//to select the correct one, talk to Jamie about it
void AdminControlls::menuOptionSelect(){


    while(this->running){
        this->displayAdminMenu();

        //this can also be inheritted
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        //input validation
        if(choice <= 0 && choice >= 5){
            std::cout << "Invalid option, please select again:" << std::endl;

            //could use here too
            std::cout << "Enter your choice: ";
            std::cin >> choice;
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
                //!!!manage coupons
                break;
            case 5:
                this->returnToMainMenu();
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
    for (auto prod : this->products_vec){
        std::cout << prod.getId() << " " << prod.getName() << " " << prod.getStock() << std::endl;
    }

}


//!!! General principle. Show inventory, ask for ID, give options, update vector (products probs)
void AdminControlls::manageInventory(){
    //view so you can actually see what is being editted, 
    //need a new condensed method to call a refreshing version of this
    bool stay_on_screen = true;
    while(stay_on_screen){
        //should refresh inventory view each time
        //need to edit the file too
        this->viewInventory();


        //need input validation here
        int ID_for_restock;
        int num_to_restock;
        std::cout << "Select ID of item to restock, enter -1 to return: ";
        std::cin >> ID_for_restock;
        std::cout << "How many items do you wish to add? " << std::endl;
        std::cin >> num_to_restock;

        //this may not work, need to check reference
        if(ID_for_restock != -1){
            products_vec[ID_for_restock - 1].addStock(num_to_restock);

        } else {
            stay_on_screen = false;
        }
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
void AdminControlls::returnToMainMenu(){
    this->running = false;
}