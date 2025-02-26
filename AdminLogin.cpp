#include <iostream>
#include "AdminLogin.h"

AdminLogin::AdminLogin(std::string un, std::string pw){
    this->username = un;
    this->password = pw;
}

bool AdminLogin::operator==(AdminLogin login_attempt){
    if(login_attempt.username == this->username && login_attempt.password == this->password){
        return true;
    } else {
        std::cout << "Incorrect Username or Password: Try again.";
        //potentially want some sort of try loop counter, maybe give this a maximum attempt number?
        //doesn't actually matter of course, just an idea. 
        return false;
    }
}

