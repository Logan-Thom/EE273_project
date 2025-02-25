#ifndef BASKET_H
#define BASKET_H

#include "Product.h"
#include <vector>
#include <utility> // For std::pair

void addToBasket(std::vector<std::pair<Product, int>>& basket, const std::vector<Product>& products);
void viewBasket(const std::vector<std::pair<Product, int>>& basket);

#endif
