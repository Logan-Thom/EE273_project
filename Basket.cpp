/*
Implementation of Basket class
Created for: EE273 E-Commerce Project
Last Updated: 08/05/25
Updated By: Logan Thom, Jamie Briggs
*/
#include "Basket.h"
#include "ECommerce.h"
#include "Checkout.h"
#include <iostream>
#include <limits>
#include <algorithm>


// Function to add a product with quantity to the basket
void Basket::addToBasket(ECommerce& ecommerce, std::vector<std::pair<std::shared_ptr<Product>, int>>& basket, const std::vector<std::shared_ptr<Product>>& products, const std::string& mode) {
    while (true) {
        std::cout << "\nEnter the Product ID to add to basket (or type 'view' to see basket, 'back' to return, 'checkout' to buy): ";
        std::string input;
        std::cin >> input;

        if (input == "view") {
            menuBasket(ecommerce,basket);
            continue;
        }
        else if (input == "back") {
            return;  // Properly exit the function
        }
        else if (input == "checkout") {
            ecommerce.checkout_utils->proceedToCheckout(ecommerce,basket);
            return;
        }

        // int productId;
        // try {
        //     productId = std::stoi(input);
        // }
        // catch (...) {
        //     std::cout << "Invalid input. Please enter a valid Product ID.\n";
        //     continue;
        // }

        std::string productId = mode + input;

        bool found = false;
        for (const auto& product : products) {
            if (productId == product->getId()) {
                int stock = product->getStock();
                int quantity = 1;

                if (stock > 1) {
                    std::cout << "Enter quantity (max " << stock << " available): ";
                    std::cin >> quantity;

                    if (std::cin.fail() || quantity <= 0) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid quantity. Please enter a positive number.\n";
                        continue;
                    }
                }


                // Check if product is already in basket
                bool existsInBasket = false;
                for (auto& item : basket) {
                    if (item.first->getId() == productId) {
                        if (item.second + quantity > stock) {
                            std::cout << "Quantity too high! Only more" << stock - item.second << " available.\n";
                            continue;
                        }
                        item.second += quantity;
                        std::cout << "Updated quantity of " << product->getName()
                            << " in basket to " << item.second << ".\n";
                        existsInBasket = true;
                        break;
                    }
                }

                if (!existsInBasket) {
                    if (quantity > stock) {
                        std::cout << "Quantity too high! Only " << stock << " available.\n";
                        continue;
                    }
                    basket.push_back(std::make_pair(product, quantity));
                    std::cout << quantity << " x " << product->getName() << " added to basket!\n";
                }

                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "Product ID not found. Try again.\n";
        }
    }
}



// Function to display the basket
void Basket::viewBasket(ECommerce& ecommerce, std::vector<std::pair<std::shared_ptr<Product>, int>>& basket) {
    ecommerce.ClearScreen();
    if (basket.empty()) {
        std::cout << "\nYour basket is empty.\n";
        ecommerce.PauseProgram();
        // ecommerce.handleMenuSelection();
        return; //attempting to stop functions
    }
    std::cout << "\n========================\n";
    std::cout << "\nYour Basket:\n";
    double total = 0.0;
    for (const auto& item : basket) {
        std::cout << item.second << " x "; // Quantity
        item.first->displayProduct(); // Product details
        total += item.first->getPrice()* item.second;
    }
    std::cout << "\nTotal: "<< static_cast<char>(156) << total;
    std::cout << "\n---------------------------------\n";
}

// Function to edit the basket
void Basket::menuBasket(ECommerce& ecommerce, std::vector<std::pair<std::shared_ptr<Product>, int>>& basket) {
    while (true) {
        this->viewBasket(ecommerce, basket);

        std::cout << "\nBasket Editing Options:\n";
        std::cout << "1. Edit quantity of an item\n";
        std::cout << "2. Remove an item\n";
        std::cout << "3. Clear the entire basket\n";
        std::cout << "4. Go back\n";
        std::cout << "5. Checkout\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1-5.\n";
            continue;
        }

        switch (choice) {
        case 1: { // Edit quantity of an item
            std::string productId;
            int newQuantity;
            std::cout << "Enter the Product ID to edit: ";
            std::cin >> productId;

            bool found = false;
            for (auto& item : basket) {
                if (item.first->getId() == productId) {
                    std::cout << "Enter new quantity: ";
                    std::cin >> newQuantity;

                    if (std::cin.fail() || newQuantity <= 0) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid quantity. Please enter a positive number.\n";
                        continue;
                    }

                    item.second = newQuantity;
                    std::cout << "Updated " << item.first->getName() << " quantity to " << newQuantity << ".\n";
                    found = true;
                    break;
                }
            }

            if (!found) {
                std::cout << "Product ID not found in basket.\n";
            }
            break;
        }

        case 2: { // Remove an item
            std::string productId;
            std::cout << "Enter the Product ID to remove: ";
            std::cin >> productId;

            auto it = std::remove_if(basket.begin(), basket.end(),
                [productId](const std::pair<std::shared_ptr<Product>, int>& item) {
                    return item.first->getId() == productId;
                });

            if (it != basket.end()) {
                std::cout << "Removed product from basket.\n";
                basket.erase(it, basket.end());
            }
            else {
                std::cout << "Product ID not found in basket.\n";
            }
            break;
        }

        case 3: // Clear the basket
            basket.clear();
            std::cout << "Basket has been cleared.\n";
            break;

        case 4: // Go back to main menu
            return;  // **Ensure function exits properly**

        case 5: // Checkout
            ecommerce.checkout_utils->proceedToCheckout(ecommerce,basket);
            return;  // **Exit menu after checkout to avoid lingering inside `menuBasket()`**

        default:
            std::cout << "Invalid choice. Please enter a number between 1-5.\n";
        }
    }
}

