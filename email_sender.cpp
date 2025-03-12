#include "email_sender.h"
#include <iostream>
#include <sstream>

#define SMTP_SERVER "smtp://smtp.gmail.com:587"
#define SENDER_EMAIL "ee273ecom@gmail.com"
#define SENDER_PASSWORD "tply zpog furr waqi"
#define SUPPLIER_EMAIL "ee273ecom@gmail.com"

struct upload_status {
    size_t bytes_read;
    std::string email_payload;
};

size_t payload_source(void* ptr, size_t size, size_t nmemb, void* userp) {
    struct upload_status* upload_ctx = (struct upload_status*)userp;
    size_t len = upload_ctx->email_payload.size() - upload_ctx->bytes_read;

    if (len > size * nmemb)
        len = size * nmemb;

    if (len > 0) {
        memcpy(ptr, upload_ctx->email_payload.c_str() + upload_ctx->bytes_read, len);
        upload_ctx->bytes_read += len;
        return len;
    }
    return 0;
}

bool send_email(const std::string& recipient, const std::string& subject, const std::string& body) {
    CURL* curl;
    CURLcode res;
    struct upload_status upload_ctx = { 0 };

    // Format the email message with headers
    upload_ctx.email_payload =
        "To: " + recipient + "\r\n"
        "From: Ecom Store <" + std::string(SENDER_EMAIL) + ">\r\n"
        "Subject: " + subject + "\r\n"
        "MIME-Version: 1.0\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "\r\n" +
        body + "\r\n";

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (!curl) {
        std::cerr << "Failed to initialize cURL" << std::endl;
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, SMTP_SERVER);
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_USERNAME, SENDER_EMAIL);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, SENDER_PASSWORD);
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "<" SENDER_EMAIL ">");

    struct curl_slist* recipients = NULL;
    recipients = curl_slist_append(recipients, ("<" + recipient + ">").c_str());
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
    curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

    res = curl_easy_perform(curl);
    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    if (res != CURLE_OK) {
        std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
        return false;
    }

    std::cout << "Email sent successfully to " << recipient << "!" << std::endl;
    return true;
}

void send_order_emails(const std::string& customer_email,
    const std::vector<std::pair<Product, int>>& basket,
    const std::string& timestamp,
    const std::string& maskedCardNumber,
    const std::string& expiryDate,
    double totalCost) {
    std::stringstream customer_body, supplier_body;

    // 📨 Customer Email - Thank You for Your Order
    customer_body << "<html><body style='font-family: Arial, sans-serif;'>"
        << "<h2 style='color: #2C3E50;'>Thank You for Your Order!</h2>"
        << "<p>Dear Customer,</p>"
        << "<p>Your order has been successfully placed. Here are your order details:</p>"
        << "<table border='1' cellpadding='8' cellspacing='0' style='border-collapse: collapse; width: 100%;'>"
        << "<tr><th>Product</th><th>Quantity</th><th>Price</th></tr>";

    for (const auto& item : basket) {
        customer_body << "<tr><td>" << item.first.getName() << "</td>"
            << "<td>" << item.second << "</td>"
            << "<td>£" << item.first.getPrice() * item.second << "</td></tr>";
    }

    customer_body << "</table><p><strong>Total Cost: £" << totalCost << "</strong></p>"
        << "<p>Thank you for shopping with us!</p></body></html>";

    send_email(customer_email, "Order Confirmation - Thank You!", customer_body.str());

    // 📨 Supplier Email - New Order Received
    supplier_body << "<html><body style='font-family: Arial, sans-serif;'>"
        << "<h2 style='color: #2C3E50;'>New Order Received</h2>"
        << "<p><strong>Timestamp:</strong> " << timestamp << "</p>"
        << "<p><strong>Payment Details:</strong></p>"
        << "<p>Card: "<< maskedCardNumber << "</p>"
        << "<p>Expiry: " << expiryDate << "</p>"
        << "<h3>Order Details:</h3>"
        << "<table border='1' cellpadding='8' cellspacing='0' style='border-collapse: collapse; width: 100%;'>"
        << "<tr><th>Product</th><th>Quantity</th><th>Price</th></tr>";

    for (const auto& item : basket) {
        supplier_body << "<tr><td>" << item.first.getName() << "</td>"
            << "<td>" << item.second << "</td>"
            << "<td>£" << item.first.getPrice() * item.second << "</td></tr>";
    }

    supplier_body << "</table><p><strong>Total Cost: £" << totalCost << "</strong></p>"
        << "<p>Please process the order as soon as possible.</p></body></html>";

    send_email(SUPPLIER_EMAIL, "New Order Received", supplier_body.str());
}