/*
Utility class to handle loading of data from external files into the program.
Created for: EE273 E-Commerce Project
Last Updated: 08/05/25
Updated By: Logan Thom, Jamie Briggs
*/


#ifndef DATABASE_H
#define DATABASE_H

#include "Product.h"
#include "Coupon.h"
#include <vector>

class Database {

public:

std::vector<Product> loadProductsFromFile();
std::vector<Product> loadServicesFromFile();
std::vector<Coupon> loadCouponsFromFile();
void save_coupons(ECommerce* ecommerce);
void updateCouponUsage(int couponID, std::vector<Coupon>& coupons);
void checkoutUpdateStock(std::vector<std::pair<Product, int>>& basket);

};


#endif