# API Documentation: E-Commerce Inventory Management Service

## Overview
This document describes the REST API endpoints, request/response formats, and conventions for the E-Commerce Inventory Management Service. All endpoints follow RESTful conventions, use JSON for data exchange, and are versioned under `/api/v1/`.

---

## General Conventions
- **Base URL:** `/api/v1/`
- **Response Structure:**
  ```json
  {
    "success": true,
    "data": { ... },
    "error": null
  }
  ```
- **Error Handling:**
  - All errors return HTTP status codes and a consistent error object:
    ```json
    {
      "success": false,
      "data": null,
      "error": {
        "code": "ERROR_CODE",
        "message": "Error description."
      }
    }
    ```
- **Authentication:** Not required (admin-only system).
- **Pagination:** Supported via `page` and `pageSize` query parameters.

---

## Endpoints

### Category
- **Create Category**
  - `POST /categories`
  - Request:
    ```json
    {
      "name": "Electronics",
      "parentCategoryId": "cat123" // optional
    }
    ```
  - Response: Created category object

- **List Categories**
  - `GET /categories`
  - Response: Array of category objects

- **Get Category by ID**
  - `GET /categories/{id}`
  - Response: Category object

- **Update Category**
  - `PUT /categories/{id}`
  - Request:
    ```json
    {
      "name": "Updated Name",
      "parentCategoryId": "cat456" // optional
    }
    ```
  - Response: Updated category object

- **Delete Category**
  - `DELETE /categories/{id}`
  - Query: `confirm=true` (required for recursive deletion)
  - Response: Success/failure

---

### Product
- **Create Product**
  - `POST /products`
  - Request:
    ```json
    {
      "name": "iPhone 15",
      "description": "Latest model...",
      "brandId": "brand123",
      "categoryId": "cat123",
      "active": true
    }
    ```
  - Response: Created product object

- **List Products**
  - `GET /products`
  - Query: `search`, `categoryId`, `page`, `pageSize`, `active`
  - Response: Array of product objects

- **Get Product by ID**
  - `GET /products/{id}`
  - Response: Product object

- **Update Product**
  - `PUT /products/{id}`
  - Request: Same as create
  - Response: Updated product object

- **Delete Product**
  - `DELETE /products/{id}`
  - Query: `confirm=true` (required for recursive deletion)
  - Response: Success/failure

---

### SKU
- **Create SKU**
  - `POST /products/{productId}/skus`
  - Request:
    ```json
    {
      "color": "Black",
      "size": "128GB",
      "price": 999.99,
      "imageUrl": "..." // optional, defaults to product image
    }
    ```
  - Response: Created SKU object

- **List SKUs for Product**
  - `GET /products/{productId}/skus`
  - Response: Array of SKU objects

- **Get SKU by ID**
  - `GET /skus/{id}`
  - Response: SKU object

- **Update SKU**
  - `PUT /skus/{id}`
  - Request: Same as create
  - Response: Updated SKU object

- **Delete SKU**
  - `DELETE /skus/{id}`
  - Query: `confirm=true` (required for recursive deletion)
  - Response: Success/failure

---

### Brand
- **Create Brand**
  - `POST /brands`
  - Request:
    ```json
    {
      "name": "Apple"
    }
    ```
  - Response: Created brand object

- **List Brands**
  - `GET /brands`
  - Response: Array of brand objects

- **Update Brand**
  - `PUT /brands/{id}`
  - Request:
    ```json
    {
      "name": "Updated Brand Name"
    }
    ```
  - Response: Updated brand object

- **Delete Brand**
  - `DELETE /brands/{id}`
  - Response: Success/failure

---

## Bulk Operations
- Supported for categories, products, and SKUs via dedicated endpoints (e.g., `POST /categories/bulk-delete`).
- Limits per request should be specified in the implementation.

---

## Audit Logging
- All create, update, and delete operations are logged with user, timestamp, entity type, and operation details.

---

## Example Error Codes
- `CATEGORY_NOT_FOUND`
- `PRODUCT_NOT_FOUND`
- `SKU_NOT_FOUND`
- `BRAND_NOT_FOUND`
- `VALIDATION_ERROR`
- `INTERNAL_ERROR`

---

## Notes
- Default image URL for SKUs is configured in the system settings.
- All endpoints return a standard response structure.
- API versioning is `/api/v1/`.

---

For further details, refer to the implementation and PRD documents.
