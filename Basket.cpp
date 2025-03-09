#include "Basket.h"
#include "menu.h"
#include "Checkout.h"
#include "screen_utilities.h"
#include <iostream>
#include <limits>


// Function to add a product with quantity to the basket
void addToBasket(std::vector<std::pair<Product, int>>& basket, const std::vector<Product>& products) {
    while (true) {
        std::cout << "\nEnter the Product ID to add to basket (or type 'view' to see basket, 'back' to return, 'checkout' to buy): ";
        std::string input;
        std::cin >> input;

        if (input == "view") {
            menuBasket(basket);
            continue;
        }
        else if (input == "back") {
            return;  // Properly exit the function
        }
        else if (input == "checkout") {
            proceedToCheckout(basket);
            return;
        }

        int productId;
        try {
            productId = std::stoi(input);
        }
        catch (...) {
            std::cout << "Invalid input. Please enter a valid Product ID.\n";
            continue;
        }

        bool found = false;
        for (const auto& product : products) {
            if (productId == product.getId()) {
                int stock = product.getStock(); // Ensure stock is available
                int quantity;
                std::cout << "Enter quantity: ";
                std::cin >> quantity;

                if (std::cin.fail() || quantity <= 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid quantity. Please enter a positive number.\n";
                    continue;
                }

                // Check if product is already in basket
                bool existsInBasket = false;
                for (auto& item : basket) {
                    if (item.first.getId() == productId) {
                        if (item.second + quantity > stock) {
                            std::cout << "Quantity too high! Only more" << stock - item.second << " available.\n";
                            continue;
                        }
                        item.second += quantity;
                        std::cout << "Updated quantity of " << product.getName()
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
                    std::cout << quantity << " x " << product.getName() << " added to basket!\n";
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
void viewBasket(std::vector<std::pair<Product, int>>& basket) {
    clearScreen();
    if (basket.empty()) {
        std::cout << "\nYour basket is empty.\n";
        pauseProgram();
        handleMenuSelection(basket);
    }
    std::cout << "\n========================\n";
    std::cout << "\nYour Basket:\n";
    double total = 0.0;
    for (const auto& item : basket) {
        std::cout << item.second << " x "; // Quantity
        item.first.displayProduct(); // Product details
        total += item.first.getPrice()* item.second;
    }
    std::cout << "\nTotal: "<< static_cast<char>(156) << total;
    std::cout << "\n---------------------------------\n";
}

// Function to edit the basket
void menuBasket(std::vector<std::pair<Product, int>>& basket) {
    while (true) {
        viewBasket(basket);

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
            int productId, newQuantity;
            std::cout << "Enter the Product ID to edit: ";
            std::cin >> productId;

            bool found = false;
            for (auto& item : basket) {
                if (item.first.getId() == productId) {
                    std::cout << "Enter new quantity: ";
                    std::cin >> newQuantity;

                    if (std::cin.fail() || newQuantity <= 0) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid quantity. Please enter a positive number.\n";
                        continue;
                    }

                    item.second = newQuantity;
                    std::cout << "Updated " << item.first.getName() << " quantity to " << newQuantity << ".\n";
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
            int productId;
            std::cout << "Enter the Product ID to remove: ";
            std::cin >> productId;

            auto it = std::remove_if(basket.begin(), basket.end(),
                [productId](const std::pair<Product, int>& item) {
                    return item.first.getId() == productId;
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
            proceedToCheckout(basket);
            return;  // **Exit menu after checkout to avoid lingering inside `menuBasket()`**

        default:
            std::cout << "Invalid choice. Please enter a number between 1-5.\n";
        }
    }
}

