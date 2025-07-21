# Project Structure: E-Commerce Inventory Management Service

## Root Directory
- `CMakeLists.txt` — CMake build configuration
- `README.md` — Project overview and instructions
- `Project_Summary_Report.md`, `Implementation_Plan.md`, `Technical_PRD.md`, `Solution_Design.md`, `Architecture_Diagram.md` — Documentation
- `coverage_html/` — Code coverage HTML reports
- `Debug/` — Compiled binaries and build output
- `build/`, `CMakeFiles/`, `cmake_install.cmake`, etc. — CMake build artifacts

## Source Code
- `src/`
  - `main.cpp` — Application entry point
  - `ConfigLoader.cpp` — Loads configuration files
  - `CategoryHandler.cpp` — Category CRUD and logic
  - `ProductHandler.cpp` — Product CRUD and logic
  - `SKUHandler.cpp` — SKU CRUD and logic
  - `AuditLogger.cpp` — Audit logging and log rotation
  - `ProductController.cpp` — REST API controller for products
  - `ProductService.cpp` — Product business logic

## Headers
- `include/`
  - `ConfigLoader.h`, `CategoryHandler.h`, `ProductHandler.h`, `SKUHandler.h`, `AuditLogger.h`, `ProductController.h`, `ProductService.h` — Class and function declarations

## Tests
- `tests/`
  - `test_main.cpp` — Test entry point
  - `test_config_loader.cpp` — ConfigLoader tests
  - `test_category_handler.cpp` — CategoryHandler tests
  - `test_product_handler.cpp` — ProductHandler tests
  - `test_sku_handler.cpp` — SKUHandler tests
  - `test_audit_logger.cpp` — AuditLogger tests
  - `test_product_controller.cpp` — ProductController tests
  - `test_product_service.cpp` — ProductService tests

## Data
- `data/`
  - `categories.json`, `products.bak`, `categories.bak`, `skus.bak` — JSON data and backups

## Logs
- `logs/`
  - `audit.log`, `audit_YYYY-MM-DD_HH-MM-SS.log`, `debug.log` — Audit and debug logs

## Other
- `config/` — Configuration files (if any)
- `docs/` — Additional documentation
- `tasks/` — Task-related files
- `Testing/` — Testing artifacts
- `x64/` — Platform-specific build output

---
This structure supports modular C++ development, robust testing, code coverage, and production-grade audit logging for an e-commerce inventory management service.
