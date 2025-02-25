#include "Basket.h"
#include "Checkout.h"
#include <iostream>
#include <limits>

// Function to add a product with quantity to the basket
void addToBasket(std::vector<std::pair<Product, int>>& basket, const std::vector<Product>& products) {
    while (true) {
        std::cout << "\nEnter the Product ID to add to basket (or type 'view' to see basket, 'back' to return, ''checkout to buy): ";
        std::string input;
        std::cin >> input;

        if (input == "view") {
            viewBasket(basket);
            continue;
        }
        else if (input == "back") {
            return;
        }
        else if (input == "checkout") {
            proceedToCheckout(basket);
            continue;
        }

        int productId;
        try {
            productId = std::stoi(input);
        }
        catch (...) {
            std::cout << "Invalid input. Please enter a valid Product ID.\n";
            continue;
        }

        // Find the product by ID
        bool found = false;
        for (const auto& product : products) {
            if (productId == product.getId()) {
                int quantity;
                std::cout << "Enter quantity: ";
                std::cin >> quantity;

                if (std::cin.fail() || quantity <= 0) {
                    std::cin.clear(); // Clear error flags
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid quantity. Please enter a positive number.\n";
                    continue;
                }

                // Add to basket
                basket.push_back(std::make_pair(product, quantity));
                std::cout << quantity << " x " << product.getName() << " added to basket!\n";
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
void viewBasket(const std::vector<std::pair<Product, int>>& basket) {
    if (basket.empty()) {
        std::cout << "\nYour basket is empty.\n";
        return;
    }

    std::cout << "\nYour Basket:\n";
    for (const auto& item : basket) {
        std::cout << item.second << " x "; // Quantity
        item.first.displayProduct(); // Product details
    }
}

