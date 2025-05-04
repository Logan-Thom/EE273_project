#include "AdminControlls.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <Vector>


void AdminControlls::displayAdminMenu(){
    this->RefreshScreen(); //inherited method from Display class
    
    std::cout << "1. View Inventory" << std::endl;
    std::cout << "2. Manage Inventory" << std::endl;
    std::cout << "3. View Order History" << std::endl;
    std::cout << "4. Return to Main Menu" << std::endl;
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
                break;
            case 2:
                this->manageInventory();
                break;
            case 3:
                std::cout << "Don't do this yet" << std::endl;
                //this.viewOrderHistory();
                break;
            case 4:
                this->returnToMainMenu();
                break;
            default:
                std::cout << "Unknown option, returning to main menu..." << std::endl;
                this->returnToMainMenu();
                break; //probably don't need to break on default
        }
    }
}

//general idea is to show each item and how many there are in stock,
//could be expanded to do so much more but keep simple for now
/*
void AdminControlls::viewInventory(){
    this->RefreshScreen();
    //file handle for read
    std::string filepath = "products.txt";
    std::ifstream productFile(filepath);

    std::string fileLine;
    std::string splitLine;
    char delimiter = ',';



    //know when to return
        while(getline (productFile, fileLine)){
            std::stringstream ss(fileLine);
            productInformation current_product;
            //go through the line;
            int i = 0;
            while(getline (ss, splitLine, delimiter)){
                if (i==0){
                    current_product.id = std::stoi(splitLine);
                } else if (i==1){
                    current_product.product_name = splitLine;
                } else if (i==2){
                    current_product.price = std::stof(splitLine);
                } else if (i==3){
                    current_product.stock = std::stoi(splitLine);
                }

                i++;
            }

            //store in vector incase of re-use
            products.push_back(current_product);

            //display for user
            std::cout << current_product.id << " " << current_product.product_name << " has " << current_product.stock << " unit(s) remaining." << std::endl;
        }
        std::cout << "========================\n";

}
*/


//lord help me
void AdminControlls::viewInventory(){
    //take the products
}

void AdminControlls::viewOrderHistory(){
   //call the orders class here
}

//currently need to run viewInventory first, which is stupid, need to put things into constructors
//and do background init tasks because the code here is dreadfully bad
//hell, this whole class needs re-written
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
            this->editProductFile(); //hate it so much, WILL be changing
        } else {
            stay_on_screen = false;
        }
    }
}

//this could maybe be a virtual/overriden function, look into it, at the least it can inherrit
void AdminControlls::editProductFile(){
    //open file for write, and write contents of vector to it.
    //this wouldn't need to exist if previous files were better
    std::ofstream productFile("products.txt");

    for(int i=0; i<products_vec.size();i++){
        productFile << products_vec[i].getId() << "," << products_vec[i].getName() << "," << products_vec[i].getPrice() << "," << products_vec[i].getStock();
    }

    productFile.close();
}

void AdminControlls::returnToMainMenu(){
    this->running = false;
}