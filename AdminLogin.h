/*
Class Header for admin login information
Created for: EE273 E-Commerce Project
Last Updated: 08/05/25
Updated By: Logan Thom, Jamie Briggs
*/

#ifndef ADMIN_H
#define ADMIN_H

#include <string>

class AdminLogin {
    private:
    std::string username;
    std::string password;

    public:
    AdminLogin(void);
    AdminLogin(std::string username, std::string password);
    bool AttemptLogin(AdminLogin login_attempt);
};
 


#endif