#pragma once
#include "ProductHandler.h"
#include "CategoryHandler.h"
#include "AuditLogger.h"
#include <string>

class ProductService {
public:
    ProductService(CategoryHandler& categoryHandler, ProductHandler& productHandler);
    bool createProduct(const Product& product, const std::string& user);
    // ...other service methods (update, delete, bulk, etc.)
private:
    CategoryHandler& categoryHandler;
    ProductHandler& productHandler;
};
