/*
Implementation of Checkout class
Created for: EE273 E-Commerce Project
Last Updated: 08/05/25
Updated By: Logan Thom, Jamie Briggs
*/
#include "Checkout.h"
#include "Database.h"
#include "Order.h"
#include "email_sender.h"
#include "ECommerce.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <limits>

// Function to generate current timestamp
std::string Checkout::getCurrentTimestamp() {
    time_t now = time(0);
    struct tm timeinfo;
    localtime_r(&now, &timeinfo); //!!!

    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", &timeinfo);
    return std::string(buffer);
}


//Coupon Prosses
double Checkout::getCouponDiscount(ECommerce& ecommerce) {
    char hasCoup;
    

    // Ask the user if they have a coupon
    std::cout << "Do you have a coupon? (Enter Y for YES or N for NO): ";
    std::cin >> hasCoup;

    // Validate input
    while (hasCoup != 'Y' && hasCoup != 'y' && hasCoup != 'N' && hasCoup != 'n') {
        std::cout << "Invalid answer. Please enter Y for YES or N for NO: ";
        std::cin >> hasCoup;
    }

    // If the user does not have a coupon, return 1
    if (hasCoup == 'N' || hasCoup == 'n') {
        return 1;
    }

    // If the user has a coupon, prompt for code
    std::string couponCode;
    std::vector<Coupon> coupons = ecommerce.GetCoupons();
    while (true) {
        std::cout << "Enter your coupon code: ";
        std::cin >> couponCode;
        
        // Check if the coupon exists
        for (Coupon& coupon : coupons) {
            if (coupon.getCode() == couponCode && coupon.isActive() && coupon.getUsed() < coupon.getMaxUses()) {
                ecommerce.database_utils->updateCouponUsage(coupon.getCouponID(), coupons); //!!! this needs to go into coupons, not database
                return coupon.getDiscountPercentage();
            }
        }

        // If no valid coupon found
        std::cout << "Invalid or expired coupon code. Try again? (Y to retry, N to continue without coupon): ";
        char retry;
        std::cin >> retry;

        if (retry == 'N' || retry == 'n') {
            return 1;
        }
    }
}


// Function to handle checkout
void Checkout::proceedToCheckout(ECommerce& ecommerce, std::vector<std::pair<std::shared_ptr<Product>, int>>& basket) {
    ecommerce.ClearScreen();
    if (basket.empty()) {
        std::cout << "\nYour basket is empty. Add products before checking out.\n\n";
        ecommerce.PauseProgram();
        return; //stop the rabit 
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
        ecommerce.PauseProgram();
        return;
    }
    std::cout << "Payment details valid \n\n";
    std::cout << "Enter Email: ";
    std::cin >> email;
    std::cout << "---------------------------------\n";
    
    double totalCost = 0.0;
    for (const auto& item : basket) {
        std::cout << item.second << " x "; // Quantity
        item.first->displayProduct(); // Product details
        totalCost += item.first->getPrice() * item.second;
    }
    std::cout << "\nTotal: " << static_cast<char>(156) << totalCost;
    std::cout << "\n---------------------------------\n";
    

    
    double couponDiscount = getCouponDiscount(ecommerce);
    
    
    totalCost *=couponDiscount;
    std::cout << "Final Cost: "<< totalCost;
    std::cout << "\n---------------------------------\n";
    std::cout << "\n";
    std::cout << "Ready to Purchase\n";
    ecommerce.PauseProgram();

    std::string current_time = getCurrentTimestamp();
    send_order_emails(email, basket, current_time, cardNumber, expiryDate, totalCost);
    ecommerce.database_utils->checkoutUpdateStock(basket);



    std::string timestamp = getCurrentTimestamp();
    Order::orderInformation order;
    for (const auto& item : basket){
        order.items_bought = basket.size();
        order.date = timestamp.substr(0,10);
        order.time = timestamp.substr(11,8);
        order.date_time = ( (stoi(order.time.substr(6,2))) + ((stoi(order.time.substr(3,2)))*100) + ((stoi(order.time.substr(0,2)))*10000) + ((stoi(order.date.substr(8,2)))*1000000) + ((stoi(order.date.substr(5,2)))*100000000) + ((stoi(order.date.substr(0,4)))*1000000000000)); //makes an int of the timestamp, useful for sorting.
        order.card_identifier = stoi(cardNumber.substr(12,4));
        order.card_expiry = expiryDate;
        order.item = item.first->getName(); //same name for both but should work because different namespaces
        order.quantity = item.second;
        order.unit_cost = item.first->getPrice();
        order.total_payment = totalCost;
        
        ecommerce.GetAdminControlls().order.AddToOrderVec(order);
    }

    // Clear the basket
    basket.clear();
    std::cout << "\nOrder placed successfully! Your basket has been cleared.\n";
    return;
}
