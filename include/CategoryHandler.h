#pragma once
#include <string>
#include <vector>
#include <optional>

struct Category {
    std::string id;
    std::string name;
    std::optional<std::string> parentCategoryId;
};

class CategoryHandler {
public:
    bool load();
    bool save();
    bool create(const Category& category);
    std::optional<Category> read(const std::string& id) const;
    bool update(const Category& category);
    bool remove(const std::string& id);
    std::vector<Category> list() const;
    bool backup(const std::string& backupPath) const;
    bool restore(const std::string& backupPath);
private:
    std::vector<Category> categories;
    bool validate(const Category& category) const;
};
