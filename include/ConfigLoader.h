#pragma once
#include <string>
#include <vector>

class ConfigLoader {
public:
    static ConfigLoader& getInstance();
    bool load();
    const std::vector<std::string>& getBrands() const;
    const std::vector<std::string>& getColors() const;
    const std::vector<std::string>& getSizes() const;
    const std::string& getDefaultImageUrl() const;
    bool isValid() const;
private:
    ConfigLoader();
    std::vector<std::string> brands;
    std::vector<std::string> colors;
    std::vector<std::string> sizes;
    std::string defaultImageUrl;
    bool valid;
};
