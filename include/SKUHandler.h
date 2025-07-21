#pragma once
#include <string>
#include <vector>
#include <optional>

struct SKU {
    std::string id;
    std::string productId;
    double price;
    std::string color;
    std::string size;
};

class SKUHandler {
public:
    bool load();
    bool save();
    bool create(const SKU& sku);
    std::optional<SKU> read(const std::string& id) const;
    bool update(const SKU& sku);
    bool remove(const std::string& id);
    std::vector<SKU> list() const;
    std::vector<SKU> listByProduct(const std::string& productId) const;
    bool backup(const std::string& backupPath) const;
    bool restore(const std::string& backupPath);
private:
    std::vector<SKU> skus;
    bool validate(const SKU& sku) const;
};
