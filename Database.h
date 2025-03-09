#ifndef DATABASE_H
#define DATABASE_H

#include "Product.h"
#include "Coupon.h"
#include <vector>

std::vector<Product> loadProductsFromFile();
std::vector<Coupon> loadCouponsFromFile();
void updateCouponUsage(int couponID, std::vector<Coupon>& coupons);
void checkoutUpdateStock(std::vector<std::pair<Product, int>>& basket);
#endif