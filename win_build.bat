@echo off
rem Windows version of the compile script, requires 32bit cURL in PATH
rem currently errors with this one when email_sender.cpp is included
g++ AdminControlls.cpp AdminLogin.cpp Basket.cpp Checkout.cpp Coupons.cpp Database.cpp Display.cpp Order.cpp Product.cpp ECommerce.cpp main.cpp 