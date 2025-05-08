/*
Implementation of Coupon class, these comments dont do much
on .cpp files, headers are far better to get an idea of what it does
Created for: EE273 E-Commerce Project
Last Updated: 08/05/25
Updated By: Logan Thom, Jamie Briggs
*/

#include "Coupon.h"
#include <iostream>


Coupon::Coupon(int id, const std::string& code, double discount, int maxUses, int used, bool active)
    : couponID(id), code(code), discountPercentage(discount), used(used), maxUses(maxUses), active(active) {
}



int Coupon::getCouponID() const { return couponID; }
std::string Coupon::getCode() const { return code; }
double Coupon::getDiscountPercentage() const { return discountPercentage; }
int Coupon::getUsed() const { return used; }
int Coupon::getMaxUses() const { return maxUses; }
bool Coupon::isActive() const { return active; }
void Coupon::usesCoupon() { used+=1; }


void Coupon::SetActive(bool activation){
    this->active = activation;
}

void Coupon::SetUses(int num){
    this->maxUses = num;
}

void Coupon::SetDiscount(float discount){
    this->discountPercentage = discount;
}