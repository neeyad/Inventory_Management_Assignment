#include <gtest/gtest.h>
#include "ProductHandler.h"
#include <filesystem>
#include <fstream>

TEST(ProductHandler, CRUD) {
    std::filesystem::create_directories("data");
    std::ofstream("data/products.json") << "[]";
    ProductHandler handler;
    handler.load();
    Product prod1{ "1", "iPhone 15", "Latest model", "Apple", "cat1", true };
    Product prod2{ "2", "T-Shirt", "Cotton", "Nike", "cat2", true };
    ASSERT_TRUE(handler.create(prod1));
    ASSERT_TRUE(handler.create(prod2));
    auto list = handler.list();
    ASSERT_EQ(list.size(), 2);
    auto readProd = handler.read("1");
    ASSERT_TRUE(readProd.has_value());
    ASSERT_EQ(readProd->name, "iPhone 15");
    prod1.name = "iPhone 15 Pro";
    ASSERT_TRUE(handler.update(prod1));
    auto updatedProd = handler.read("1");
    ASSERT_EQ(updatedProd->name, "iPhone 15 Pro");
    ASSERT_TRUE(handler.remove("2"));
    ASSERT_EQ(handler.list().size(), 1);
}

TEST(ProductHandler, BackupRestore) {
    std::filesystem::create_directories("data");
    std::ofstream("data/products.json") << "[]";
    ProductHandler handler;
    handler.create({ "1", "iPhone 15", "Latest model", "Apple", "cat1", true });
    ASSERT_TRUE(handler.backup("data/products.bak"));
    handler.remove("1");
    ASSERT_EQ(handler.list().size(), 0);
    ASSERT_TRUE(handler.restore("data/products.bak"));
    handler.load(); // Ensure reload after restore
    ASSERT_EQ(handler.list().size(), 1);
}

TEST(ProductHandler, Validation) {
    ProductHandler handler;
    std::remove("data/products.json");
    ASSERT_FALSE(handler.create({ "1", "", "desc", "brand", "cat1", true })); // empty name
    ASSERT_FALSE(handler.create({ "2", "name", "", "brand", "cat1", true })); // empty description
    ASSERT_FALSE(handler.create({ "3", "name", "desc", "", "cat1", true })); // empty brand
    ASSERT_FALSE(handler.create({ "4", "name", "desc", "brand", "", true })); // empty categoryId
}
