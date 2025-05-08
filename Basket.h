/*
Utility class header for functionality relating to the order basket
Created for: EE273 E-Commerce Project
Last Updated: 08/05/25
Updated By: Logan Thom, Jamie Briggs
*/

#ifndef BASKET_H
#define BASKET_H

#include "Product.h"
#include "ECommerce.h"
#include <vector>
#include <utility> // For std::pair



class ECommerce;

class Basket {

public:

void addToBasket(ECommerce& ecommerce, std::vector<std::pair<Product, int>>& basket, const std::vector<Product>& products, const std::string& mode);
void viewBasket(ECommerce& ecommerce, std::vector<std::pair<Product, int>>& basket);
void menuBasket(ECommerce& ecommerce, std::vector<std::pair<Product, int>>& basket); // New function for editing basket

};
#endif
