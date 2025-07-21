#include <gtest/gtest.h>
#include "CategoryHandler.h"
#include <filesystem>
#include <fstream>

TEST(CategoryHandler, CRUD) {
    std::filesystem::create_directories("data");
    std::ofstream("data/categories.json") << "[]";
    CategoryHandler handler;
    handler.load();
    Category cat1{ "1", "Electronics", std::nullopt };
    Category cat2{ "2", "Apparel", std::nullopt };
    ASSERT_TRUE(handler.create(cat1));
    ASSERT_TRUE(handler.create(cat2));
    auto list = handler.list();
    ASSERT_EQ(list.size(), 2);
    auto readCat = handler.read("1");
    ASSERT_TRUE(readCat.has_value());
    ASSERT_EQ(readCat->name, "Electronics");
    cat1.name = "Electronics Updated";
    ASSERT_TRUE(handler.update(cat1));
    auto updatedCat = handler.read("1");
    ASSERT_EQ(updatedCat->name, "Electronics Updated");
    ASSERT_TRUE(handler.remove("2"));
    ASSERT_EQ(handler.list().size(), 1);
}

TEST(CategoryHandler, BackupRestore) {
    std::filesystem::create_directories("data");
    std::ofstream("data/categories.json") << "[]";
    CategoryHandler handler;
    handler.create({ "1", "Electronics", std::nullopt });
    ASSERT_TRUE(handler.backup("data/categories.bak"));
    handler.remove("1");
    ASSERT_EQ(handler.list().size(), 0);
    ASSERT_TRUE(handler.restore("data/categories.bak"));
    handler.load(); // Ensure reload after restore
    ASSERT_EQ(handler.list().size(), 1);
}

TEST(CategoryHandler, Validation) {
    CategoryHandler handler;
    std::remove("data/categories.json");
    handler.create({ "1", "Electronics", std::nullopt });
    ASSERT_FALSE(handler.create({ "2", "Electronics", std::nullopt })); // duplicate name
    ASSERT_FALSE(handler.create({ "3", "", std::nullopt })); // empty name
}
