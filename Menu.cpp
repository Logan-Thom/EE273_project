#include "Menu.h"
#include "Basket.h"
#include "Database.h"
#include "screen_utilities.h"
#include "Product.h"
#include <iostream>
#include <vector>
#include <limits>
#include <set>
#include <map>
#include <memory>

int getTotalBasketItems(const std::vector<std::pair<std::shared_ptr<Product>, int>>& basket) {
    int totalItems = 0;
    for (const auto& item : basket) {
        totalItems += 1;
    }
    return totalItems;
}

void displayMainMenu(const std::vector<std::pair<std::shared_ptr<Product>, int>>& basket) {
    clearScreen();
    int basketCount = getTotalBasketItems(basket);

    std::cout << "\n========================\n";
    std::cout << "    E-Commerce System   \n";
    std::cout << "========================\n";
    std::cout << "1. Log in as Admin\n";
    std::cout << "2. Browse Products/Services\n";
    std::cout << "3. View Basket (" << basketCount << ")\n";
    std::cout << "4. Exit\n";
    std::cout << "========================\n";
}

void handleMenuSelection(std::vector<std::pair<std::shared_ptr<Product>, int>>& basket) {
    bool running = true;

    while (running) {
        displayMainMenu(basket);

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
            pauseProgram();
            break;
        case 2: {
            clearScreen();
            std::cout << "Browse Options:\n";
            std::cout << "1. Browse Products\n";
            std::cout << "2. Browse Services\n";
            std::cout << "Enter your choice: ";

            int browseChoice;
            std::cin >> browseChoice;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input.\n";
                pauseProgram();
                break;
            }

            if (browseChoice == 1) {
                browseItems(loadProductsFromFile(), basket, "Products", "P");
            }
            else if (browseChoice == 2) {
                browseItems(loadServicesFromFile(), basket, "Services", "S");
            }
            else {
                std::cout << "Invalid option.\n";
                pauseProgram();
            }
            break;
        }
        case 3:
            clearScreen();
            menuBasket(basket);
            break;
        case 4:
            std::cout << "Exiting the system. Goodbye!\n";
            running = false;
            return;
        default:
            std::cout << "Invalid choice! Please enter a number between 1 and 4.\n";
        }
    }
}

void browseItems(const std::vector<std::shared_ptr<Product>>& items,
    std::vector<std::pair<std::shared_ptr<Product>, int>>& basket,
    const std::string& label,
    const std::string& mode) {
    clearScreen();

    if (items.empty()) {
        std::cout << "No " << label << " found.\n";
        pauseProgram();
        return;
    }

    std::map<std::string, int> categoryCount;
    for (const auto& item : items) {
        categoryCount[item->getCategory()]++;
    }

    std::vector<std::string> categoryList;
    categoryList.push_back("All");

    std::cout << "\nSelect a category to browse " << label << ":\n";
    int index = 1;
    std::cout << index++ << ". All (" << items.size() << ")\n";

    for (const auto& pair : categoryCount) {
        categoryList.push_back(pair.first);
        std::cout << index++ << ". " << pair.first << " (" << pair.second << ")\n";
    }

    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (std::cin.fail() || choice < 1 || choice > static_cast<int>(categoryList.size())) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Returning...\n";
        pauseProgram();
        return;
    }

    std::string selectedCategory = categoryList[choice - 1];

    clearScreen();
    std::cout << "\nAvailable " << label << " (" << selectedCategory << "):\n";
    bool found = false;

    for (const auto& item : items) {
        if (selectedCategory == "All" || item->getCategory() == selectedCategory) {
            item->displayProduct();
            found = true;
        }
    }

    if (!found) {
        std::cout << "No " << label << " found in this category.\n";
    }

    addToBasket(basket, items, mode);
}
