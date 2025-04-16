#ifndef DATABASE_H
#define DATABASE_H

#include "Product.h"
#include "Service.h"
#include "Coupon.h"
#include <vector>
#include <memory>

std::vector<std::shared_ptr<Product>> loadProductsFromFile();
std::vector<std::shared_ptr<Product>> loadServicesFromFile();
void addOrdertoDB(std::string timestamp, std::string maskedCardNumber, std::string expiryDate, std::string email, int couponID, const std::vector<std::pair<std::shared_ptr<Product>, int>>& basket);
std::vector<Coupon> loadCouponsFromFile();
void updateCouponUsage(int couponID, std::vector<Coupon>& coupons);
void checkoutUpdateStock(const std::vector<std::pair<std::shared_ptr<Product>, int>>& basket);

#endif
