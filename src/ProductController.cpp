#include "ProductController.h"
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

ProductController::ProductController(const std::string& baseUrl)
    : listener(utility::conversions::to_string_t(baseUrl)) {
    listener.support(methods::GET, std::bind(&ProductController::handleGet, this, std::placeholders::_1));
    listener.support(methods::POST, std::bind(&ProductController::handlePost, this, std::placeholders::_1));
    listener.support(methods::PUT, std::bind(&ProductController::handlePut, this, std::placeholders::_1));
    listener.support(methods::DEL, std::bind(&ProductController::handleDelete, this, std::placeholders::_1));
}

void ProductController::open() { listener.open().wait(); }
void ProductController::close() { listener.close().wait(); }

void ProductController::handleGet(http_request request) {
    auto products = handler.list();
    json::value arr = json::value::array(products.size());
    for (size_t i = 0; i < products.size(); ++i) {
        arr[i][U("id")] = json::value::string(utility::conversions::to_string_t(products[i].id));
        arr[i][U("name")] = json::value::string(utility::conversions::to_string_t(products[i].name));
        arr[i][U("description")] = json::value::string(utility::conversions::to_string_t(products[i].description));
        arr[i][U("brand")] = json::value::string(utility::conversions::to_string_t(products[i].brand));
        arr[i][U("categoryId")] = json::value::string(utility::conversions::to_string_t(products[i].categoryId));
        arr[i][U("active")] = json::value::boolean(products[i].active);
    }
    json::value response;
    response[U("success")] = json::value::boolean(true);
    response[U("data")] = arr;
    response[U("error")] = json::value::null();
    request.reply(status_codes::OK, response);
}

void ProductController::handlePost(http_request request) {
    request.extract_json().then([this, request](json::value body) {
        Product p;
        p.id = utility::conversions::to_utf8string(body[U("id")].as_string());
        p.name = utility::conversions::to_utf8string(body[U("name")].as_string());
        p.description = utility::conversions::to_utf8string(body[U("description")].as_string());
        p.brand = utility::conversions::to_utf8string(body[U("brand")].as_string());
        p.categoryId = utility::conversions::to_utf8string(body[U("categoryId")].as_string());
        p.active = body[U("active")].as_bool();
        json::value response;
        if (handler.create(p)) {
            response[U("success")] = json::value::boolean(true);
            response[U("data")] = json::value::string(U("Product created"));
            response[U("error")] = json::value::null();
            request.reply(status_codes::Created, response);
        } else {
            response[U("success")] = json::value::boolean(false);
            response[U("data")] = json::value::null();
            response[U("error")] = json::value::string(U("Validation failed"));
            request.reply(status_codes::BadRequest, response);
        }
    });
}

void ProductController::handlePut(http_request request) {
    request.extract_json().then([this, request](json::value body) {
        Product p;
        p.id = utility::conversions::to_utf8string(body[U("id")].as_string());
        p.name = utility::conversions::to_utf8string(body[U("name")].as_string());
        p.description = utility::conversions::to_utf8string(body[U("description")].as_string());
        p.brand = utility::conversions::to_utf8string(body[U("brand")].as_string());
        p.categoryId = utility::conversions::to_utf8string(body[U("categoryId")].as_string());
        p.active = body[U("active")].as_bool();
        json::value response;
        if (handler.update(p)) {
            response[U("success")] = json::value::boolean(true);
            response[U("data")] = json::value::string(U("Product updated"));
            response[U("error")] = json::value::null();
            request.reply(status_codes::OK, response);
        } else {
            response[U("success")] = json::value::boolean(false);
            response[U("data")] = json::value::null();
            response[U("error")] = json::value::string(U("Update failed"));
            request.reply(status_codes::BadRequest, response);
        }
    });
}

void ProductController::handleDelete(http_request request) {
    auto id = utility::conversions::to_utf8string(request.relative_uri().path());
    if (!id.empty() && id.front() == '/') id = id.substr(1);
    json::value response;
    if (handler.remove(id)) {
        response[U("success")] = json::value::boolean(true);
        response[U("data")] = json::value::string(U("Product deleted"));
        response[U("error")] = json::value::null();
        request.reply(status_codes::OK, response);
    } else {
        response[U("success")] = json::value::boolean(false);
        response[U("data")] = json::value::null();
        response[U("error")] = json::value::string(U("Delete failed"));
        request.reply(status_codes::BadRequest, response);
    }
}
