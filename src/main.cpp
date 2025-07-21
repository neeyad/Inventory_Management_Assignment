#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <iostream>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

int main() {
    http_listener listener(U("http://localhost:8080/api/v1/health"));
    listener.support(methods::GET, [](http_request request) {
        json::value response;
        response[U("success")] = json::value::boolean(true);
        response[U("data")] = json::value::string(U("Service is running"));
        response[U("error")] = json::value::null();
        request.reply(status_codes::OK, response);
    });
    try {
        listener.open().wait();
        std::wcout << L"Service running at http://localhost:8080/api/v1/health" << std::endl;
        std::wcout << L"Press ENTER to stop the service..." << std::endl;
        std::wstring line;
        std::getline(std::wcin, line);
        listener.close().wait();
    } catch (const std::exception& ex) {
        std::cerr << "Failed to start service: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
