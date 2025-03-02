#include "Menu.h"
#include <vector>

int main() {
    std::vector<std::pair<Product, int>> basket;

    while (true) {
        handleMenuSelection(basket);
        break;  // **Break out of the loop when user exits**
    }

    return 0;
}
