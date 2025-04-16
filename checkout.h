#ifndef CHECKOUT_H
#define CHECKOUT_H

#include <vector>
#include "Product.h"
#include <utility> // For std::pair
#include "Basket.h"

void proceedToCheckout(std::vector<std::pair<std::shared_ptr<Product>, int>>& basket);
std::pair<int, double> getCoupon();
#endif
#pragma once
