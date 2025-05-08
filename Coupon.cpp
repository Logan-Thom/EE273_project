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


