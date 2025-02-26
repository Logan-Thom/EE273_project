#include "Menu.h"
#include "Basket.h"
#include "Database.h"
#include "AdminLogin.h"
#include <iostream>
#include <vector>
#include <limits>

// Function to display the main menu
void displayMainMenu() {
    std::cout << "\n========================\n";
    std::cout << "    E-Commerce System   \n";
    std::cout << "========================\n";
    std::cout << "1. Log in as Admin\n";
    std::cout << "2. Browse Products\n";
    std::cout << "3. View Basket\n";
    std::cout << "4. Exit\n";
    std::cout << "========================\n";
}

// Function to handle menu selection
void handleMenuSelection() {
    std::vector<std::pair<Product, int>> basket; // Stores selected products with quantity

    while (true) {
        displayMainMenu();

        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1:
            std::cout << "Admin login not implemented yet.\n";
            waitForUser();
            break;
        case 2:
            browseProducts(basket);
            break;
        case 3:
            viewBasket(basket);
            waitForUser();
            break;
        case 4:
            std::cout << "Exiting the system. Goodbye!\n";
            return;
        default:
            std::cout << "Invalid choice! Please enter a number between 1 and 4.\n";
        }
    }
}

// Function to browse products and allow adding to basket
void browseProducts(std::vector<std::pair<Product, int>>& basket) {
    std::vector<Product> products = loadProductsFromFile("products.txt");

    if (products.empty()) {
        std::cout << "No products found.\n";
    }
    else {
        std::cout << "\nAvailable Products:\n";
        for (const auto& product : products) {
            product.displayProduct();
        }
    }

    addToBasket(basket, products);
}

// Function to pause before returning to menu
void waitForUser() {
    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void adminLogIn() {
    //idea for advanced feature
    //set login credentials as a struct of username and password
    //operator overload the = to see if they are correct, easy marks
    //ran out of time before lab, will implement later

    AdminLogin correct_details("root","toor");
    
    std::string usrnm;
    std::string pswrd;
    std::cout << "\nusername: ";
    std::cin >> usrnm;
    std::cout << "\npassword: ";
    std::cin >> pswrd;

    

    AdminLogin* adminloginptr = new AdminLogin(usrnm, pswrd);

    //input validation time!!!
    if(*adminloginptr == correct_details){
        delete[] adminloginptr;
        //correct, do something 
    } else {
        //incorrect, do something
    }
}
