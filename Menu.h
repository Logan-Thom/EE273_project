#ifndef MENU_H
#define MENU_H

#include <vector>
#include "Product.h"
#include <utility> // For std::pair

void displayMainMenu();
void handleMenuSelection();
void browseProducts(std::vector<std::pair<Product, int>>& basket);
void waitForUser();

#endif
