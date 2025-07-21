#include <gtest/gtest.h>
#include "ConfigLoader.h"
#include <cstdlib>

TEST(ConfigLoader, LoadsValidConfig) {
    _putenv_s("ECOM_BRANDS", "Nike,Adidas,Puma");
    _putenv_s("ECOM_COLORS", "Red,Blue,Green");
    _putenv_s("ECOM_SIZES", "S,M,L");
    _putenv_s("ECOM_DEFAULT_IMAGE_URL", "http://example.com/default.jpg");
    auto& loader = ConfigLoader::getInstance();
    ASSERT_TRUE(loader.load());
    EXPECT_EQ(loader.getBrands().size(), 3);
    EXPECT_EQ(loader.getColors().size(), 3);
    EXPECT_EQ(loader.getSizes().size(), 3);
    EXPECT_EQ(loader.getDefaultImageUrl(), "http://example.com/default.jpg");
    EXPECT_TRUE(loader.isValid());
}

TEST(ConfigLoader, InvalidConfigMissingEnv) {
    _putenv_s("ECOM_BRANDS", "");
    _putenv_s("ECOM_COLORS", "");
    _putenv_s("ECOM_SIZES", "");
    _putenv_s("ECOM_DEFAULT_IMAGE_URL", "");
    auto& loader = ConfigLoader::getInstance();
    ASSERT_FALSE(loader.load());
    EXPECT_FALSE(loader.isValid());
}
