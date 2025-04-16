#include "Basket.h"
#include "menu.h"
#include "Checkout.h"
#include "screen_utilities.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <memory>
#include <iomanip>

// Function to add a product with quantity to the basket
void addToBasket(std::vector<std::pair<std::shared_ptr<Product>, int>>& basket, const std::vector<std::shared_ptr<Product>>& products, const std::string& mode) {
    while (true) {
        std::cout << "\nEnter the Product ID to add to basket (or type 'view' to see basket, 'back' to return, 'checkout' to buy): ";
        std::string input;
        std::cin >> input;

        if (input == "view") {
            clearScreen();
            menuBasket(basket);
            return;
        }
        else if (input == "back") {
            return;
        }
        else if (input == "checkout") {
            proceedToCheckout(basket);
            return;
        }

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

                bool existsInBasket = false;
                for (auto& item : basket) {
                    if (item.first->getId() == productId) {
                        if (item.second + quantity > stock) {
                            std::cout << "Sorry, we only have " << stock << " in stock. Please enter a smaller quantity.\n";
                            existsInBasket = true;
                            break;
                        }
                        item.second += quantity;
                        std::cout << quantity << " more added. You now have " << item.second << " x " << product->getName() << " in your basket.\n";
                        existsInBasket = true;
                        break;
                    }
                }

                if (!existsInBasket) {
                    if (quantity > stock) {
                        std::cout << "Sorry, we only have " << stock << " in stock. Please enter a smaller quantity.\n";
                        continue;
                    }
                    basket.push_back(std::make_pair(product, quantity));
                    if (stock == 1) {
                        std::cout << product->getName() << " (Service) added to your basket.\n";
                    }
                    else {
                        std::cout << "Added " << quantity << " x " << product->getName() << " to your basket.\n";
                    }
                }

                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "No product found with that ID. Please try again.\n";
        }
    }
}

// Function to display the basket
void viewBasket(std::vector<std::pair<std::shared_ptr<Product>, int>>& basket) {
    if (basket.empty()) {
        std::cout << "\nYour basket is empty.\n";
        pauseProgram();
        handleMenuSelection(basket);
        return;
    }

    std::cout << "\n========================\n";
    std::cout << "\nYour Basket:\n";

    double total = 0.0;
    int index = 1;

    for (const auto& item : basket) {

        std::cout << std::setw(2) << index++ << ". "
            << std::setw(4) << item.second << " x ";
        item.first->displayProduct();
        total += item.first->getPrice() * item.second;
    }

    std::cout << "\nTotal: " << static_cast<char>(156) << total;
    std::cout << "\n---------------------------------\n";
}


// Function to edit the basket
void menuBasket(std::vector<std::pair<std::shared_ptr<Product>, int>>& basket) {
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
        case 1: {
            int index;
            std::cout << "Enter the basket index to edit: ";
            std::cin >> index;

            if (std::cin.fail() || index < 1 || index > static_cast<int>(basket.size())) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                clearScreen();
                std::cout << "Invalid index.\n";
                continue;
            }

            auto& selectedItem = basket[index - 1];
            int stock = selectedItem.first->getStock();

            if (stock == 1) {
                clearScreen();
                std::cout << "This is a service. Quantity cannot be changed.\n";
                continue;
            }

            int newQuantity;
            while (true) {
                std::cout << "Enter new quantity (max " << stock << "): ";
                std::cin >> newQuantity;

                if (!std::cin.fail() && newQuantity > 0 && newQuantity <= stock) {
                    selectedItem.second = newQuantity;
                    clearScreen();
                    std::cout << "Updated " << selectedItem.first->getName() << " quantity to " << newQuantity << ".\n";
                    break;
                }
                else {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid quantity. Please enter a number between 1 and " << stock << ".\n";
                }
            }
            break;
        }

        case 2: {
            int index;
            std::cout << "Enter the basket index to remove: ";
            std::cin >> index;

            if (std::cin.fail() || index < 1 || index > static_cast<int>(basket.size())) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                clearScreen();
                std::cout << "Invalid index.\n";
                continue;
            }

            std::cout << "Removed " << basket[index - 1].first->getName() << " from basket.\n";
            basket.erase(basket.begin() + (index - 1));
            clearScreen();
            break;
        }

        case 3:
            basket.clear();
            clearScreen();
            std::cout << "Basket has been cleared.\n";

            break;

        case 4:
            return;

        case 5:
            proceedToCheckout(basket);
            return;

        default:
            clearScreen();
            std::cout << "Invalid choice. Please enter a number between 1-5.\n";
        }
    }
}