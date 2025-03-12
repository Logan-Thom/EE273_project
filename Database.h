#ifndef DATABASE_H
#define DATABASE_H

#include "Product.h"
#include "Coupon.h"
#include <vector>

std::vector<Product> loadProductsFromFile();
void addOrdertoDB(std::string timestamp, std::string cardNumber, std::string expiryDate, std::string email, int couponID, std::vector<std::pair<Product, int>>& basket);
std::vector<Coupon> loadCouponsFromFile();
void updateCouponUsage(int couponID, std::vector<Coupon>& coupons);
void checkoutUpdateStock(std::vector<std::pair<Product, int>>& basket);
#endif