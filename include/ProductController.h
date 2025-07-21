#pragma once
#include <cpprest/http_listener.h>
#include "ProductHandler.h"

class ProductController {
public:
    ProductController(const std::string& baseUrl);
    void open();
    void close();
    void handleGet(web::http::http_request request);
    void handlePost(web::http::http_request request);
    void handlePut(web::http::http_request request);
    void handleDelete(web::http::http_request request);
private:
    web::http::experimental::listener::http_listener listener;
    ProductHandler handler;
};
