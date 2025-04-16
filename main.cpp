#include "Menu.h"
#include <vector>
#include <memory> // Needed for std::shared_ptr

int main() {
    std::vector<std::pair<std::shared_ptr<Product>, int>> basket;

    while (true) {
        handleMenuSelection(basket);
        break;  // **Break out of the loop when user exits**
    }

    return 0;
}
