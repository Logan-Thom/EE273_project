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

