#include <gtest/gtest.h>
#include "SKUHandler.h"
#include <filesystem>
#include <fstream>

TEST(SKUHandler, CRUD) {
    std::filesystem::create_directories("data");
    std::ofstream("data/skus.json") << "[]";
    SKUHandler handler;
    handler.load();
    SKU sku1{ "1", "prod1", 999.99, "Red", "L" };
    SKU sku2{ "2", "prod2", 19.99, "Blue", "M" };
    ASSERT_TRUE(handler.create(sku1));
    ASSERT_TRUE(handler.create(sku2));
    auto list = handler.list();
    ASSERT_EQ(list.size(), 2);
    auto readSku = handler.read("1");
    ASSERT_TRUE(readSku.has_value());
    ASSERT_EQ(readSku->color, "Red");
    sku1.color = "Green";
    ASSERT_TRUE(handler.update(sku1));
    auto updatedSku = handler.read("1");
    ASSERT_EQ(updatedSku->color, "Green");
    ASSERT_TRUE(handler.remove("2"));
    ASSERT_EQ(handler.list().size(), 1);
}

TEST(SKUHandler, BackupRestore) {
    std::filesystem::create_directories("data");
    std::ofstream("data/skus.json") << "[]";
    SKUHandler handler;
    handler.create({ "1", "prod1", 999.99, "Red", "L" });
    ASSERT_TRUE(handler.backup("data/skus.bak"));
    handler.remove("1");
    ASSERT_EQ(handler.list().size(), 0);
    ASSERT_TRUE(handler.restore("data/skus.bak"));
    handler.load(); // Ensure reload after restore
    ASSERT_EQ(handler.list().size(), 1);
}

TEST(SKUHandler, Validation) {
    SKUHandler handler;
    std::remove("data/skus.json");
    ASSERT_FALSE(handler.create({ "1", "", 999.99, "Red", "L" })); // empty productId
    ASSERT_FALSE(handler.create({ "2", "prod2", -1, "Blue", "M" })); // negative price
    ASSERT_FALSE(handler.create({ "3", "prod3", 19.99, "", "M" })); // empty color
    ASSERT_FALSE(handler.create({ "4", "prod4", 19.99, "Blue", "" })); // empty size
}
