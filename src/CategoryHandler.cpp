#include "CategoryHandler.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool CategoryHandler::load() {
    std::ifstream file("data/categories.json");
    if (!file.is_open()) {
        // Create empty file if missing
        std::ofstream createFile("data/categories.json");
        createFile << "[]";
        categories.clear();
        return true;
    }
    std::filesystem::create_directories("data");
    json j;
    try {
    std::filesystem::create_directories("data");
    if (!std::filesystem::exists("data/categories.json")) {
        std::ofstream createFile("data/categories.json");
        createFile << "[]";
        createFile.close();
    }
        file >> j;
    } catch (...) {
        j = json::array();
    }
    categories.clear();
    for (const auto& item : j) {
        Category c;
        c.id = item["id"].get<std::string>();
        c.name = item["name"].get<std::string>();
        if (item.contains("parentCategoryId"))
            c.parentCategoryId = item["parentCategoryId"].get<std::string>();
        categories.push_back(c);
    }
    return true;
}

bool CategoryHandler::save() {
    json j = json::array();
    for (const auto& c : categories) {
        json item;
        item["id"] = c.id;
        item["name"] = c.name;
        if (c.parentCategoryId)
            item["parentCategoryId"] = *c.parentCategoryId;
        j.push_back(item);
    }
    std::filesystem::create_directories("data");
    std::ofstream file("data/categories.json");
    if (!file.is_open()) return false;
    file << j.dump(2);
    return true;
}

bool CategoryHandler::create(const Category& category) {
    std::filesystem::create_directories("logs");
    std::ofstream debug("logs/debug.log", std::ios::app);
    if (!validate(category)) {
        debug << "[CategoryHandler::create] Validation failed\n";
        return false;
    }
    categories.push_back(category);
    bool saved = save();
    if (!saved) debug << "[CategoryHandler::create] Save failed\n";
    return saved;
}

std::optional<Category> CategoryHandler::read(const std::string& id) const {
    for (const auto& c : categories) {
        if (c.id == id) return c;
    }
    return std::nullopt;
}

bool CategoryHandler::update(const Category& category) {
    for (auto& c : categories) {
        if (c.id == category.id) {
            c = category;
            return save();
        }
    }
    return false;
}

bool CategoryHandler::remove(const std::string& id) {
    auto it = std::remove_if(categories.begin(), categories.end(), [&](const Category& c) { return c.id == id; });
    if (it == categories.end()) return false;
    categories.erase(it, categories.end());
    return save();
}

std::vector<Category> CategoryHandler::list() const {
    return categories;
}

bool CategoryHandler::backup(const std::string& backupPath) const {
    // Ensure source file exists
    std::filesystem::create_directories("data");
    std::ifstream src("data/categories.json", std::ios::binary);
    if (!src.is_open()) {
        std::ofstream createFile("data/categories.json");
        createFile << "[]";
        src.open("data/categories.json", std::ios::binary);
    }
    std::filesystem::create_directories("data");
    if (!std::filesystem::exists("data/categories.json")) {
        std::ofstream createFile("data/categories.json");
        createFile << "[]";
        createFile.close();
    }
    std::ofstream dst(backupPath, std::ios::binary);
    std::filesystem::create_directories("logs");
    std::ofstream debug("logs/debug.log", std::ios::app);
    if (!src.is_open()) debug << "[CategoryHandler::backup] Source file open failed\n";
    if (!dst.is_open()) debug << "[CategoryHandler::backup] Dest file open failed\n";
    if (!src.is_open() || !dst.is_open()) return false;
    dst << src.rdbuf();
    return true;
}

bool CategoryHandler::restore(const std::string& backupPath) {
    std::filesystem::create_directories("data");
    std::ifstream src(backupPath, std::ios::binary);
    if (!src.is_open()) {
        std::ofstream createFile(backupPath);
        createFile << "[]";
        src.open(backupPath, std::ios::binary);
    }
    std::ofstream dst("data/categories.json", std::ios::binary);
    if (!src.is_open() || !dst.is_open()) return false;
    dst << src.rdbuf();
    return load();
}

bool CategoryHandler::validate(const Category& category) const {
    if (category.name.empty()) return false;
    for (const auto& c : categories) {
        if (c.name == category.name) return false; // unique name
    }
    return true;
}
