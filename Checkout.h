/*
Utility class header for functionality relating to checkout 
Created for: EE273 E-Commerce Project
Last Updated: 08/05/25
Updated By: Logan Thom, Jamie Briggs
*/

#ifndef CHECKOUT_H
#define CHECKOUT_H

#include <vector>
#include <string>
#include "Product.h"
#include "ECommerce.h"
#include <utility> // For std::pair
#include "Basket.h"

class ECommerce;

class Checkout {

public: 

void proceedToCheckout(ECommerce& ecommerce, std::vector<std::pair<Product, int>>& basket);
double getCouponDiscount(ECommerce& ecommerce);
std::string getCurrentTimestamp();

};
#endif

