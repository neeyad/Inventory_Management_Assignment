cmake_minimum_required(VERSION 3.10)
project(ECommerceInventoryService)

set(CMAKE_CXX_STANDARD 17)

# Enable coverage flags for GCC/Clang
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0" CACHE STRING "" FORCE)
endif()

# vcpkg integration
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
endif()

find_package(cpprestsdk REQUIRED)
find_package(GTest REQUIRED)

include_directories(include)


# Add all source files for handlers, controllers, services, and audit logger
set(SRC_FILES
    src/main.cpp
    src/ConfigLoader.cpp
    src/CategoryHandler.cpp
    src/ProductHandler.cpp
    src/SKUHandler.cpp
    src/AuditLogger.cpp
    src/ProductController.cpp
    src/ProductService.cpp
)

add_executable(ECommerceInventoryService ${SRC_FILES})
target_link_libraries(ECommerceInventoryService PRIVATE cpprestsdk::cpprest)

# Add all test files
set(TEST_FILES
    tests/test_main.cpp
    tests/test_config_loader.cpp
    tests/test_category_handler.cpp
    tests/test_product_handler.cpp
    tests/test_sku_handler.cpp
    tests/test_audit_logger.cpp
    tests/test_product_controller.cpp
    tests/test_product_service.cpp
    src/ConfigLoader.cpp
    src/CategoryHandler.cpp
    src/ProductHandler.cpp
    src/SKUHandler.cpp
    src/AuditLogger.cpp
    src/ProductController.cpp
    src/ProductService.cpp
)

add_executable(UnitTests ${TEST_FILES})
target_link_libraries(UnitTests PRIVATE cpprestsdk::cpprest GTest::gtest GTest::gtest_main)

# Register the test executable with CTest
enable_testing()
add_test(NAME UnitTests COMMAND UnitTests)
