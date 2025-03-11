#ifndef CHECKOUT_H
#define CHECKOUT_H

#include <vector>
#include "Product.h"
#include <utility> // For std::pair

void proceedToCheckout(std::vector<std::pair<Product, int>>& basket);

#endif
#pragma once
