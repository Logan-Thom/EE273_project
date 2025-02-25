#include "Checkout.h"
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


// Function to handle checkout
void proceedToCheckout(std::vector<std::pair<Product, int>>& basket) {
    if (basket.empty()) {
        std::cout << "\nYour basket is empty. Add products before checking out.\n";
        return;
    }

    std::string cardNumber, expiryDate, cvv;
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
        return;
    }

    // Calculate total cost
    double totalCost = 0.0;
    for (const auto& item : basket) {
        totalCost += item.first.getPrice() * item.second;
    }

    // Save order details to file
    std::ofstream orderFile("orders.txt", std::ios::app);
    if (!orderFile) {
        std::cerr << "Error: Could not open orders.txt to save the order.\n";
        return;
    }

    std::string timestamp = getCurrentTimestamp();
    orderFile << timestamp << ","
        << "XXXX-XXXX-XXXX-" << cardNumber.substr(12, 4) << ","
        << expiryDate << ",";

    for (const auto& item : basket) {
        orderFile << item.first.getName() << "," << item.second << "," << item.first.getPrice() << ",";
    }

    orderFile << totalCost << "\n"; // Save total cost at the end

    orderFile.close();


    // Clear the basket
    basket.clear();
    std::cout << "\nOrder placed successfully! Your basket has been cleared.\n";
}
