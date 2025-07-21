#include "ProductService.h"

ProductService::ProductService(CategoryHandler& categoryHandler, ProductHandler& productHandler)
    : categoryHandler(categoryHandler), productHandler(productHandler) {}

bool ProductService::createProduct(const Product& product, const std::string& user) {
    // Refresh categories in case new ones were added
    categoryHandler.load();
    // Validate category exists
    auto cat = categoryHandler.read(product.categoryId);
    if (!cat.has_value()) return false;
    // Create product
    bool result = productHandler.create(product);
    // Audit log
    if (result) {
        AuditLogger::getInstance().log(user, "Product", "create");
    }
    return result;
}
