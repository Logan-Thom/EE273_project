#ifndef BASKET_H
#define BASKET_H

#include "Product.h"
#include <vector>
#include <utility> // For std::pair

class Basket {

public:

void addToBasket(ECommerce& ecommerce, std::vector<std::pair<Product, int>>& basket, const std::vector<Product>& products);
void viewBasket(ECommerce& ecommerce, std::vector<std::pair<Product, int>>& basket);
void menuBasket(ECommerce& ecommerce, std::vector<std::pair<Product, int>>& basket); // New function for editing basket

};
#endif
