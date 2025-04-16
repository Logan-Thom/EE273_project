#ifndef MENU_H
#define MENU_H

#include <vector>
#include <memory>   // Required for std::shared_ptr
#include <string>
#include "Product.h"
#include <utility>  // For std::pair

int getTotalBasketItems(const std::vector<std::pair<std::shared_ptr<Product>, int>>& basket);
void displayMainMenu(const std::vector<std::pair<std::shared_ptr<Product>, int>>& basket);
void handleMenuSelection(std::vector<std::pair<std::shared_ptr<Product>, int>>& basket);

void browseItems(const std::vector<std::shared_ptr<Product>>& items,
    std::vector<std::pair<std::shared_ptr<Product>, int>>& basket,
    const std::string& label,
    const std::string& mode);

#endif
