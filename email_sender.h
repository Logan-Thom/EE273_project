/*
Header for use of email sending functionality 
Created for: EE273 E-Commerce Project
Last Updated: 08/05/25
Updated By: Logan Thom, Jamie Briggs
*/

#ifndef EMAIL_SENDER_H
#define EMAIL_SENDER_H

#include <curl/curl.h>
#include <vector>
#include <string>
#include <utility>
#include <memory>       // For std::shared_ptr
#include "Product.h"    // For shared_ptr<Product>

bool send_email(const std::string& recipient,
    const std::string& subject,
    const std::string& body);

// Updated to accept basket with shared_ptr<Product>
void send_order_emails(const std::string& customer_email,
    const std::vector<std::pair<Product, int>>& basket,
    const std::string& timestamp,
    const std::string& maskedCardNumber,
    const std::string& expiryDate,
    double totalCost);

#endif // EMAIL_SENDER_H
