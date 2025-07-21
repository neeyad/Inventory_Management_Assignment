#include "ConfigLoader.h"
#include <cstdlib>
#include <sstream>

namespace {
    std::vector<std::string> split(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delimiter)) {
            if (!item.empty()) tokens.push_back(item);
        }
        return tokens;
    }
}

ConfigLoader& ConfigLoader::getInstance() {
    static ConfigLoader instance;
    return instance;
}

ConfigLoader::ConfigLoader() : valid(false) {}

bool ConfigLoader::load() {
    const char* brandsEnv = std::getenv("ECOM_BRANDS");
    const char* colorsEnv = std::getenv("ECOM_COLORS");
    const char* sizesEnv = std::getenv("ECOM_SIZES");
    const char* imageEnv = std::getenv("ECOM_DEFAULT_IMAGE_URL");
    if (!brandsEnv || !colorsEnv || !sizesEnv || !imageEnv) {
        valid = false;
        return false;
    }
    brands = split(brandsEnv, ',');
    colors = split(colorsEnv, ',');
    sizes = split(sizesEnv, ',');
    defaultImageUrl = imageEnv;
    valid = !brands.empty() && !colors.empty() && !sizes.empty() && !defaultImageUrl.empty();
    return valid;
}

const std::vector<std::string>& ConfigLoader::getBrands() const { return brands; }
const std::vector<std::string>& ConfigLoader::getColors() const { return colors; }
const std::vector<std::string>& ConfigLoader::getSizes() const { return sizes; }
const std::string& ConfigLoader::getDefaultImageUrl() const { return defaultImageUrl; }
bool ConfigLoader::isValid() const { return valid; }
