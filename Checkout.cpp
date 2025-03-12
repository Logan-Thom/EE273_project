#include "Checkout.h"
#include "Database.h"
#include "email_sender.h"
#include "menu.h"
#include "screen_utilities.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <limits>

// Function to generate current timestamp
std::string getCurrentTimestamp() {
    time_t now = time(0);
    struct tm timeinfo;
    localtime_s(&timeinfo, &now); // Secure version

    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", &timeinfo);
    return std::string(buffer);
}



std::pair<int, double> getCoupon() {
    char hasCoup;

    // Ask the user if they have a coupon
    std::cout << "Do you have a coupon? (Enter Y for YES or N for NO): ";
    std::cin >> hasCoup;

    // Validate input
    while (hasCoup != 'Y' && hasCoup != 'y' && hasCoup != 'N' && hasCoup != 'n') {
        std::cout << "Invalid answer. Please enter Y for YES or N for NO: ";
        std::cin >> hasCoup;
    }

    // If the user does not have a coupon, return {0, 1.0} (no discount)
    if (hasCoup == 'N' || hasCoup == 'n') {
        return { 0, 1.0 };
    }

    // If the user has a coupon, prompt for code
    std::string couponCode;
    std::vector<Coupon> coupons = loadCouponsFromFile();

    while (true) {
        std::cout << "Enter your coupon code: ";
        std::cin >> couponCode;

        // Check if the coupon exists
        for (Coupon& coupon : coupons) {
            if (coupon.getCode() == couponCode && coupon.isActive() && coupon.getUsed() < coupon.getMaxUses()) {
                updateCouponUsage(coupon.getCouponID(), coupons);
                return { coupon.getCouponID(), coupon.getDiscountPercentage() };
            }
        }

        // If no valid coupon found
        std::cout << "Invalid or expired coupon code. Try again? (Y to retry, N to continue without coupon): ";
        char retry;
        std::cin >> retry;

        if (retry == 'N' || retry == 'n') {
            return { 0, 1.0 };  // Return default values (no discount)
        }
    }
}



// Function to handle checkout
void proceedToCheckout(std::vector<std::pair<Product, int>>& basket) {
    clearScreen();
    if (basket.empty()) {
        std::cout << "\nYour basket is empty. Add products before checking out.\n\n";
        pauseProgram();
        handleMenuSelection(basket);
    }
    
    std::string cardNumber, expiryDate, cvv, email;
    std::cout << "\n================ Checkout ================\n";
    std::cout << "Enter your payment details:\n";
    
    std::cout << "Card Number (16 digits): ";
    std::cin >> cardNumber;
    std::cout << "Expiry Date (MM/YY): ";
    std::cin >> expiryDate;
    std::cout << "CVV (3 digits): ";
    std::cin >> cvv;
    
    // Validate card details
    if (cardNumber.length() != 16 || expiryDate.length() != 5 || cvv.length() != 3) {
        std::cout << "Invalid payment details! Please try again.\n";
        pauseProgram();
        return;
    }
    std::cout << "Payment details valid \n\n";
    std::cout << "Enter Email: ";
    std::cin >> email;
    std::cout << "---------------------------------\n";
    
    double totalCost = 0.0;
    for (const auto& item : basket) {
        std::cout << item.second << " x "; // Quantity
        item.first.displayProduct(); // Product details
        totalCost += item.first.getPrice() * item.second;
    }
    std::cout << "\nTotal: " << static_cast<char>(156) << totalCost;
    std::cout << "\n---------------------------------\n";
    

    
    std::pair<int, double> couponData = getCoupon();
    int couponID = couponData.first;
    double couponDiscount = couponData.second;
    

    
    totalCost *=couponDiscount;
    std::cout << "Final Cost: "<< totalCost;
    std::cout << "\n---------------------------------\n";
    std::cout << "\n";
    std::cout << "Ready to Purchase\n";
    pauseProgram();


    checkoutUpdateStock(basket);

    std::string timestamp = getCurrentTimestamp();
 
    addOrdertoDB(timestamp, cardNumber, expiryDate, email, couponID, basket);
    std::string maskedCardNumber = "XXXX-XXXX-XXXX-" + cardNumber.substr(12, 4);;

    send_order_emails(email, basket, timestamp, maskedCardNumber, expiryDate, totalCost);


    // Clear the basket
    basket.clear();
    std::cout << "\nOrder placed successfully! Your basket has been cleared.\n";
    return;
}
