#include <gtest/gtest.h>
#include "ProductController.h"

// Note: For real API tests, use HTTP client to send requests to the running service.
// Here, we just verify controller construction and basic open/close.

TEST(ProductController, Construction) {
    ProductController controller("http://localhost:8080/api/v1/products");
    ASSERT_NO_THROW(controller.open());
    ASSERT_NO_THROW(controller.close());
}
