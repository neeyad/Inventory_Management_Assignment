#include <gtest/gtest.h>
#include "ProductController.h"

#include <cpprest/http_msg.h>
#include <cpprest/json.h>
#include <cpprest/http_client.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

// Note: For real API tests, use HTTP client to send requests to the running service.
// Here, we just verify controller construction and basic open/close.

TEST(ProductController, Construction) {
    ProductController controller("http://localhost:8080/api/v1/products");
    ASSERT_NO_THROW(controller.open());
    ASSERT_NO_THROW(controller.close());
}

TEST(ProductController, HandleGet) {
    ProductController controller("http://localhost:8080/api/v1/products");
    http_request req(methods::GET);
    // Should not throw when handling GET
    ASSERT_NO_THROW(controller.handleGet(req));
}

TEST(ProductController, HandlePost_Valid) {
    ProductController controller("http://localhost:8080/api/v1/products");
    http_request req(methods::POST);
    json::value body;
    body[U("id")] = json::value::string(U("1"));
    body[U("name")] = json::value::string(U("Test Product"));
    body[U("description")] = json::value::string(U("Desc"));
    body[U("brand")] = json::value::string(U("Brand"));
    body[U("categoryId")] = json::value::string(U("cat1"));
    body[U("active")] = json::value::boolean(true);
    req.set_body(body);
    ASSERT_NO_THROW(controller.handlePost(req));
}

TEST(ProductController, HandlePut_Valid) {
    ProductController controller("http://localhost:8080/api/v1/products");
    http_request req(methods::PUT);
    json::value body;
    body[U("id")] = json::value::string(U("1"));
    body[U("name")] = json::value::string(U("Test Product Updated"));
    body[U("description")] = json::value::string(U("Desc"));
    body[U("brand")] = json::value::string(U("Brand"));
    body[U("categoryId")] = json::value::string(U("cat1"));
    body[U("active")] = json::value::boolean(true);
    req.set_body(body);
    ASSERT_NO_THROW(controller.handlePut(req));
}

TEST(ProductController, HandleDelete) {
    ProductController controller("http://localhost:8080/api/v1/products");
    http_request req(methods::DEL);
    req.set_request_uri(U("/1"));
    ASSERT_NO_THROW(controller.handleDelete(req));
}
