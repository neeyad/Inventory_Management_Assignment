# E-Commerce Inventory Management Service

## Overview
A production-grade C++ REST API for managing categories, products, and SKUs, with audit logging, backup/restore, and full test coverage. Built with CppRestSDK, Google Test, and AWS CodePipeline.

## Features
- RESTful API endpoints for Category, Product, SKU, Brand
- JSON file-based storage
- Audit logging with rotation and retention
- Backup/restore utilities
- Configurable via environment variables
- Automated tests and CI/CD
- Swagger documentation at `/api/v1/docs`

## Build & Run
1. Install dependencies via vcpkg (CppRestSDK, GTest, nlohmann-json)
2. Configure environment variables:
   - `ECOM_BRANDS`, `ECOM_COLORS`, `ECOM_SIZES`, `ECOM_DEFAULT_IMAGE_URL`
3. Build with CMake:
   ```sh
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```
4. Run the service:
   ```sh
   ./ECommerceInventoryService
   ```
5. Run tests:
   ```sh
   ./UnitTests
   ```

## Deployment
- Automated via AWS CodePipeline to EC2

## API Documentation
- See `/api/v1/docs` for Swagger UI

## Backup & Restore
- Data files in `/data` folder
- Use handler backup/restore methods

## Audit Logging
- Logs stored in `/logs` folder
- Automatic rotation and retention (30 days)

## Coverage
- Coverage report generated via gcov/lcov (see `/coverage`)

## Contact
- For issues, open a ticket in this repository.
