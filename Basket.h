#ifndef BASKET_H
#define BASKET_H

#include "Product.h"
#include <vector>
#include <memory>   // For std::shared_ptr
#include <utility>  // For std::pair

void addToBasket(std::vector<std::pair<std::shared_ptr<Product>, int>>& basket,
    const std::vector<std::shared_ptr<Product>>& products,
    const std::string& mode);

void viewBasket(const std::vector<std::pair<std::shared_ptr<Product>, int>>& basket);

void menuBasket(std::vector<std::pair<std::shared_ptr<Product>, int>>& basket);

#endif
