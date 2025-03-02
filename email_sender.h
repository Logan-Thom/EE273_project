#ifndef EMAIL_SENDER_H
#define EMAIL_SENDER_H

#include <curl/curl.h>
#include <vector>
#include <string>
#include <utility>
#include "Product.h" // Assuming you have a Product class with getName() and getPrice()

bool send_email(const std::string& recipient,
    const std::string& subject,
    const std::string& body);

void send_order_emails(const std::string& customer_email,
    const std::vector<std::pair<Product, int>>& basket,
    const std::string& timestamp,
    const std::string& maskedCardNumber,
    const std::string& expiryDate,
    double totalCost);

#endif // EMAIL_SENDER_H
