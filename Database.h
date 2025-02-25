#ifndef DATABASE_H
#define DATABASE_H

#include "Product.h"
#include <vector>

std::vector<Product> loadProductsFromFile(const std::string& filename);

#endif

