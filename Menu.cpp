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
int getTotalBasketItems(const std::vector<std::pair<Product, int>>& basket) {
    int totalItems = 0;
    for (const auto& item : basket) {
        totalItems += 1; // Sum up the quantities of all products
    }
    return totalItems;
}
// Function to display the main menu
void displayMainMenu(const std::vector<std::pair<Product, int>>& basket) {
    clearScreen();
    int basketCount = getTotalBasketItems(basket); // Get total item count

    std::cout << "\n========================\n";
    std::cout << "    E-Commerce System   \n";
    std::cout << "========================\n";
    std::cout << "1. Log in as Admin\n";
    std::cout << "2. Browse Products\n";
    std::cout << "3. View Basket (" << basketCount << ")\n"; // Display item count
    std::cout << "4. Exit\n";
    std::cout << "========================\n";
}

// Function to handle menu selection
void handleMenuSelection(std::vector<std::pair<Product, int>>& basket) {
    bool running = true; // Control variable to manage loop

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
            pauseProgram;
            break;
        case 2:
            browseProducts(basket); // Ensure this function fully exits before returning
            break;
        case 3:
            menuBasket(basket);
            break;
        case 4:
            std::cout << "Exiting the system. Goodbye!\n";
            running = false; // Stop the loop
            return; // Exit function immediately
        default:
            std::cout << "Invalid choice! Please enter a number between 1 and 4.\n";
        }
    }
}



void browseProducts(std::vector<std::pair<Product, int>>& basket) {
    clearScreen();
    std::vector<Product> products = loadProductsFromFile("products.txt");

    if (products.empty()) {
        std::cout << "No products found.\n";
        return;
    }

    // Count products in each category
    std::map<std::string, int> categoryCount;
    for (const auto& product : products) {
        categoryCount[product.getCategory()]++;
    }

    // Store categories in a vector for menu display
    std::vector<std::string> categoryList;
    categoryList.push_back("All"); // 'All' option to show all products

    std::cout << "\nSelect a category to browse:\n";
    int index = 1;

    // Display the 'All' option with total product count
    std::cout << index++ << ". All (" << products.size() << ")\n";

    // Display individual categories with product counts
    for (const auto& pair : categoryCount) {
        categoryList.push_back(pair.first);
        std::cout << index++ << ". " << pair.first << " (" << pair.second << ")\n";
    }

    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    // Validate user input
    if (std::cin.fail() || choice < 1 || choice > categoryList.size()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Returning to menu...\n";
        return;
    }

    std::string selectedCategory = categoryList[choice - 1];

    // Display filtered products
    clearScreen();
    std::cout << "\nAvailable Products (" << selectedCategory << "):\n";
    bool found = false;

    for (const auto& product : products) {
        if (selectedCategory == "All" || product.getCategory() == selectedCategory) {
            product.displayProduct();
            found = true;
        }
    }

    if (!found) {
        std::cout << "No products found in this category.\n";
    }

    addToBasket(basket, products);

    // Clear input buffer to avoid unwanted behavior
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


