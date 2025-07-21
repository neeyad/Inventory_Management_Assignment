# API Documentation

## Base URL
`http://localhost:8080/api/v1/`

## Endpoints

### Health Check
- `GET /api/v1/health`
- Response: `{ success: true, data: "Service is running", error: null }`

### Products
- `GET /api/v1/products` — List all products
- `POST /api/v1/products` — Create product
- `PUT /api/v1/products` — Update product
- `DELETE /api/v1/products/{id}` — Delete product
- Request/Response: JSON, standard structure `{ success, data, error }`

### Categories
- `GET /api/v1/categories` — List all categories
- `POST /api/v1/categories` — Create category
- `PUT /api/v1/categories` — Update category
- `DELETE /api/v1/categories/{id}` — Delete category

### SKUs
- `GET /api/v1/skus` — List all SKUs
- `POST /api/v1/skus` — Create SKU
- `PUT /api/v1/skus` — Update SKU
- `DELETE /api/v1/skus/{id}` — Delete SKU

### Brands
- `GET /api/v1/brands` — List all brands
- `POST /api/v1/brands` — Create brand
- `PUT /api/v1/brands` — Update brand
- `DELETE /api/v1/brands/{id}` — Delete brand

## Error Codes
- 200 OK: Success
- 201 Created: Resource created
- 400 Bad Request: Validation or input error
- 404 Not Found: Resource not found
- 500 Internal Server Error: Unexpected error

## Example Request
```json
POST /api/v1/products
{
  "id": "1",
  "name": "iPhone 15",
  "description": "Latest model",
  "brand": "Apple",
  "categoryId": "cat1",
  "active": true
}
```

## Example Response
```json
{
  "success": true,
  "data": "Product created",
  "error": null
}
```
