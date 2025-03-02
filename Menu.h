#ifndef MENU_H
#define MENU_H

#include <vector>
#include "Product.h"
#include <utility> // For std::pair
int getTotalBasketItems(const std::vector<std::pair<Product, int>>& basket);
void displayMainMenu(const std::vector<std::pair<Product, int>>& basket);
void handleMenuSelection(std::vector<std::pair<Product, int>>& basket);
void browseProducts(std::vector<std::pair<Product, int>>& basket);
void waitForUser();

#endif

