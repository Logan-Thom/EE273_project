#ifndef CHECKOUT_H
#define CHECKOUT_H

#include <vector>
#include "Product.h"
#include <utility> // For std::pair
#include "Basket.h"

void proceedToCheckout(std::vector<std::pair<Product, int>>& basket);
double getCouponDiscount();
#endif
#pragma once
