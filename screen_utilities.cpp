#include "screen_utilities.h"
#include <iostream>


void pauseProgram() {
    std::cout << "\n";
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input
    std::cin.get(); // Wait for Enter key
}
void clearScreen() {
    std::cout << "\033[2J\033[1;1H"; // ANSI escape codes to clear the screen
}

