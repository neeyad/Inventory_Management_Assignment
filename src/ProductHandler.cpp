#include "ProductHandler.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool ProductHandler::load() {
    std::filesystem::create_directories("data");
    std::ifstream file("data/products.json");
    if (!file.is_open()) {
        std::ofstream createFile("data/products.json");
        createFile << "[]";
        products.clear();
        return true;
    }
    std::filesystem::create_directories("data");
    if (!std::filesystem::exists("data/products.json")) {
        std::ofstream createFile("data/products.json");
        createFile << "[]";
        createFile.close();
    }
    json j;
    try {
        file >> j;
    } catch (...) {
        j = json::array();
    }
    products.clear();
    for (const auto& item : j) {
        Product p;
        p.id = item["id"].get<std::string>();
        p.name = item["name"].get<std::string>();
        p.description = item["description"].get<std::string>();
        p.brand = item["brand"].get<std::string>();
        p.categoryId = item["categoryId"].get<std::string>();
        p.active = item["active"].get<bool>();
        products.push_back(p);
    }
    return true;
}

bool ProductHandler::save() {
    std::filesystem::create_directories("data");
    json j = json::array();
    for (const auto& p : products) {
        json item;
        item["id"] = p.id;
        item["name"] = p.name;
        item["description"] = p.description;
        item["brand"] = p.brand;
        item["categoryId"] = p.categoryId;
        item["active"] = p.active;
        j.push_back(item);
    }
    std::ofstream file("data/products.json");
    if (!file.is_open()) return false;
    file << j.dump(2);
    return true;
}

bool ProductHandler::create(const Product& product) {
    std::filesystem::create_directories("logs");
    std::ofstream debug("logs/debug.log", std::ios::app);
    if (!validate(product)) {
        debug << "[ProductHandler::create] Validation failed\n";
        return false;
    }
    products.push_back(product);
    bool saved = save();
    if (!saved) debug << "[ProductHandler::create] Save failed\n";
    return saved;
}

std::optional<Product> ProductHandler::read(const std::string& id) const {
    for (const auto& p : products) {
        if (p.id == id) return p;
    }
    return std::nullopt;
}

bool ProductHandler::update(const Product& product) {
    for (auto& p : products) {
        if (p.id == product.id) {
            p = product;
            return save();
        }
    }
    return false;
}

bool ProductHandler::remove(const std::string& id) {
    auto it = std::remove_if(products.begin(), products.end(), [&](const Product& p) { return p.id == id; });
    if (it == products.end()) return false;
    products.erase(it, products.end());
    return save();
}

std::vector<Product> ProductHandler::list() const {
    return products;
}

bool ProductHandler::backup(const std::string& backupPath) const {
    std::filesystem::create_directories("data");
    std::ifstream src("data/products.json", std::ios::binary);
    if (!src.is_open()) {
        std::ofstream createFile("data/products.json");
        createFile << "[]";
        src.open("data/products.json", std::ios::binary);
    }
    std::filesystem::create_directories("data");
    if (!std::filesystem::exists("data/products.json")) {
        std::ofstream createFile("data/products.json");
        createFile << "[]";
        createFile.close();
    }
    std::ofstream dst(backupPath, std::ios::binary);
    std::filesystem::create_directories("logs");
    std::ofstream debug("logs/debug.log", std::ios::app);
    if (!src.is_open()) debug << "[ProductHandler::backup] Source file open failed\n";
    if (!dst.is_open()) debug << "[ProductHandler::backup] Dest file open failed\n";
    if (!src.is_open() || !dst.is_open()) return false;
    dst << src.rdbuf();
    return true;
}

bool ProductHandler::restore(const std::string& backupPath) {
    std::filesystem::create_directories("data");
    std::ifstream src(backupPath, std::ios::binary);
    if (!src.is_open()) {
        std::ofstream createFile(backupPath);
        createFile << "[]";
        src.open(backupPath, std::ios::binary);
    }
    std::ofstream dst("data/products.json", std::ios::binary);
    if (!src.is_open() || !dst.is_open()) return false;
    dst << src.rdbuf();
    return load();
}

bool ProductHandler::validate(const Product& product) const {
    if (product.name.empty() || product.description.empty() || product.brand.empty() || product.categoryId.empty()) return false;
    return true;
}
