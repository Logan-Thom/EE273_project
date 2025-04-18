#include "Display.h"
#include <stdio.h>

Display::ClearScreen(){
    std::cout << "\033[2J\033[1:1H";
}

Display::PauseProgram(){
    std::cout << "\nPress Enter to continue..."; << std::endl
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignores the leftover buffer
    std::cin.get();
}

Display::DisplayHeader(){
    std::cout << "\n========================\n";
    std::cout << "    E-Commerce System   \n";
    std::cout << "========================\n";
}

Display::RefreshScreen(){
    Display::ClearScreen();
    Display::DisplayHeader();
}
