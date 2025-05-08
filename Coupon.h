/*
Class structure to hold data for various coupons used in the system
Created for: EE273 E-Commerce Project
Last Updated: 08/05/25
Updated By: Logan Thom, Jamie Briggs
*/

#ifndef COUPON_H
#define COUPON_H

#include <string>

class Coupon {
private:
    int couponID;
    std::string code;
    double discountPercentage;
    int used;
    int maxUses;
    bool active;

public:
    // Constructor
    Coupon(int id, const std::string& code, double discount, int maxUses, int used = 0, bool active = true);

    // Getters
    int getCouponID() const;
    std::string getCode() const;
    double getDiscountPercentage() const;
    int getUsed() const;
    int getMaxUses() const;
    bool isActive() const;
    void usesCoupon();
    void SetUses(int uses_remaining);
    void SetActive(bool activation);
    void SetDiscount(float discount);
 

};

#endif
