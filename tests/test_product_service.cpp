#include <gtest/gtest.h>
#include "ProductService.h"
#include "CategoryHandler.h"
#include "ProductHandler.h"
#include <filesystem>
#include <fstream>

TEST(ProductService, CreateProductWithValidCategory) {
    std::filesystem::create_directories("data");
    std::ofstream("data/categories.json") << "[]";
    std::ofstream("data/products.json") << "[]";
    CategoryHandler catHandler;
    ProductHandler prodHandler;
    catHandler.create({ "cat1", "Electronics", std::nullopt });
    ProductService service(catHandler, prodHandler);
    Product prod{ "1", "iPhone 15", "Latest model", "Apple", "cat1", true };
    ASSERT_TRUE(service.createProduct(prod, "admin"));
}

TEST(ProductService, CreateProductWithInvalidCategory) {
    std::remove("data/categories.json");
    std::remove("data/products.json");
    CategoryHandler catHandler;
    ProductHandler prodHandler;
    ProductService service(catHandler, prodHandler);
    Product prod{ "1", "iPhone 15", "Latest model", "Apple", "catX", true };
    ASSERT_FALSE(service.createProduct(prod, "admin"));
}
