#include "SKUHandler.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool SKUHandler::load() {
    std::filesystem::create_directories("data");
    std::ifstream file("data/skus.json");
    if (!file.is_open()) {
        std::ofstream createFile("data/skus.json");
        createFile << "[]";
        createFile.close();
    }
    json j;
    try {
        file >> j;
    } catch (...) {
        j = json::array();
    }
    skus.clear();
    for (const auto& item : j) {
        SKU s;
        s.id = item["id"].get<std::string>();
        s.productId = item["productId"].get<std::string>();
        s.price = item["price"].get<double>();
        s.color = item["color"].get<std::string>();
        s.size = item["size"].get<std::string>();
        skus.push_back(s);
    }
    return true;
}

bool SKUHandler::save() {
    std::filesystem::create_directories("data");
    json j = json::array();
    for (const auto& s : skus) {
        json item;
        item["id"] = s.id;
        item["productId"] = s.productId;
        item["price"] = s.price;
        item["color"] = s.color;
        item["size"] = s.size;
        j.push_back(item);
    }
    std::ofstream file("data/skus.json");
    if (!file.is_open()) return false;
    file << j.dump(2);
    return true;
}

bool SKUHandler::create(const SKU& sku) {
    std::filesystem::create_directories("logs");
    std::ofstream debug("logs/debug.log", std::ios::app);
    if (!validate(sku)) {
        debug << "[SKUHandler::create] Validation failed\n";
        return false;
    }
    skus.push_back(sku);
    bool saved = save();
    if (!saved) debug << "[SKUHandler::create] Save failed\n";
    return saved;
}

std::optional<SKU> SKUHandler::read(const std::string& id) const {
    for (const auto& s : skus) {
        if (s.id == id) return s;
    }
    return std::nullopt;
}

bool SKUHandler::update(const SKU& sku) {
    for (auto& s : skus) {
        if (s.id == sku.id) {
            s = sku;
            return save();
        }
    }
    return false;
}

bool SKUHandler::remove(const std::string& id) {
    auto it = std::remove_if(skus.begin(), skus.end(), [&](const SKU& s) { return s.id == id; });
    if (it == skus.end()) return false;
    skus.erase(it, skus.end());
    return save();
}

std::vector<SKU> SKUHandler::list() const {
    return skus;
}

std::vector<SKU> SKUHandler::listByProduct(const std::string& productId) const {
    std::vector<SKU> result;
    for (const auto& s : skus) {
        if (s.productId == productId) result.push_back(s);
    }
    return result;
}

bool SKUHandler::backup(const std::string& backupPath) const {
    std::filesystem::create_directories("data");
    std::ifstream src("data/skus.json", std::ios::binary);
    if (!src.is_open()) {
        std::ofstream createFile("data/skus.json");
        createFile << "[]";
        createFile.close();
        src.open("data/skus.json", std::ios::binary);
    }
    std::ofstream dst(backupPath, std::ios::binary);
    std::filesystem::create_directories("logs");
    std::ofstream debug("logs/debug.log", std::ios::app);
    if (!src.is_open()) debug << "[SKUHandler::backup] Source file open failed\n";
    if (!dst.is_open()) debug << "[SKUHandler::backup] Dest file open failed\n";
    if (!src.is_open() || !dst.is_open()) return false;
    dst << src.rdbuf();
    return true;
}

bool SKUHandler::restore(const std::string& backupPath) {
    std::filesystem::create_directories("data");
    std::ifstream src(backupPath, std::ios::binary);
    if (!src.is_open()) {
        std::ofstream createFile(backupPath);
        createFile << "[]";
        src.open(backupPath, std::ios::binary);
    }
    std::ofstream dst("data/skus.json", std::ios::binary);
    if (!src.is_open() || !dst.is_open()) return false;
    dst << src.rdbuf();
    return load();
}

bool SKUHandler::validate(const SKU& sku) const {
    if (sku.productId.empty() || sku.color.empty() || sku.size.empty() || sku.price < 0) return false;
    return true;
}
