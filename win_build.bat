@echo off
rem Windows version of the compile script, requires 32bit cURL in PATH
rem do not know if this works, I do not have a windows machine to test it, if you do, then my condolences
g++ AdminControlls.cpp AdminLogin.cpp Basket.cpp Checkout.cpp Coupons.cpp Database.cpp Display.cpp Order.cpp Product.cpp ECommerce.cpp main.cpp 