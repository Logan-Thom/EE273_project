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
            this->vector_of_products.push_back(current_product);

            //display for user
            std::cout << current_product.id << " " << current_product.product_name << " has " << current_product.stock << " unit(s) remaining." << std::endl;
        }
        std::cout << "========================\n";

}

//potentially want to be able to sort this?
//this doesn't work currently, was having a 
/*
**************************************************************************
**************************************************************************
                    NOTE FOR JAMIE
                    This doesn't work, I was checking over it
                    and hated it so much I had to delete, will
                    do ASAP, so many ideas here\
**************************************************************************
**************************************************************************
*/
void AdminControlls::viewOrderHistory(){
    //god knows what the namespaces are meant to be here
    std::string filepath = "orders.txt";
    std::ifstream ordersFile(filepath);

    std::string fileLine;

    int countOfCommas = 0;
    int numberOfItemsBought = 1;
    this->orderStruct;
    int num_of_orders = 1;
    while(getline (ordersFile, fileLine)){
        //take each line, delimit by ',', count occurrences of this character
        //use to determine how many items bought, hard coded number sadly but constant
        //put information (and convert types where appropriate) into struct
        //put struct into vector or list, test which is better

        //this is messy, and that makes me sad
        // TW: nested loops
        countOfCommas = 0;
        for(int i=0; i<fileLine.size(); i++){
            if(fileLine[i] == ','){
                countOfCommas++;
            }
        }

        //default count is 6 for a 1 item purchase, increasing items by 1 increases commas by 2, will always be even
        //use this to find item count
        numberOfItemsBought = ((countOfCommas - 4) >> 1); //bit shift because faster, I'm used to MCU programming in C this is NOT AI this is just how my brain works


        //would be nice to have a (ascii please) graph of total money each day for last month?
        //view by month?
        //menu to sort all those options?
        //hell yeah, do that here



        /*
        The idea here is to put it all into a vector for sorting potential, doing later I guess?
        why do I never comment when I'm writing code this is idiotic

        int items_bought; 
        std::string date;
        std::string time;
        int card_identifier;
        std::string item;
        int quantity;
        float unit_cost;
        float total_payment
        
        orderStruct.items_bought = numberOfItemsBought;
        orderStruct.date = fileLine.substr(0,10);
        orderStruct.time = fileLine.substr(11,8);
        orderStruct.card_identifier = stoi(fileLine.substr(35,4));
        
        //this needs to be 'lambda'ed. smiles all around
        //come back later
        */


        //num_of_orders++;
    }

    ordersFile.close();
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
            this->vector_of_products[ID_for_restock - 1].stock += num_to_restock;
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

    for(int i=0; i<vector_of_products.size();i++){
        productFile << vector_of_products[i].id << "," << vector_of_products[i].product_name << "," << vector_of_products[i].price << "," << vector_of_products[i].stock;
    }

    productFile.close();
}

void AdminControlls::returnToMainMenu(){
    this->running = false;
}