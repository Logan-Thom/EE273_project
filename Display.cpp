/*
Implementation of Display class
Created for: EE273 E-Commerce Project
Last Updated: 08/05/25
Updated By: Logan Thom, Jamie Briggs
*/
#include "Display.h"
#include <stdio.h>
#include <iostream>
#include <limits>

void Display::ClearScreen(){
    std::cout << "\033[2J\033[1:1H";
}

void Display::PauseProgram(){
    std::cout << "\nPress Enter to continue..." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //ignores the leftover buffer, uses <limits>
    std::cin.get();
}

void Display::DisplayHeader(){
    std::cout << "\n========================\n";
    std::cout << "    E-Commerce System   \n";
    std::cout << "========================\n";
}

void Display::RefreshScreen(){
    Display::ClearScreen();
    Display::DisplayHeader();
}
