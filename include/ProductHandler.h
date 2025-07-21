#pragma once
#include <string>
#include <vector>
#include <optional>

struct Product {
    std::string id;
    std::string name;
    std::string description;
    std::string brand;
    std::string categoryId;
    bool active;
};

class ProductHandler {
public:
    bool load();
    bool save();
    bool create(const Product& product);
    std::optional<Product> read(const std::string& id) const;
    bool update(const Product& product);
    bool remove(const std::string& id);
    std::vector<Product> list() const;
    bool backup(const std::string& backupPath) const;
    bool restore(const std::string& backupPath);
private:
    std::vector<Product> products;
    bool validate(const Product& product) const;
};
