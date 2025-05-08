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