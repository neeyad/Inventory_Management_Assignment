E-Commerce  Inventory Management Service
1. Purpose

This PRD defines the requirements for a simple e-commerce inventory management service. Use coding assistants like GitHub Copilot, Cursor OR Windsurf and your preferred framework to build it.

We are not focusing on authentication or authorization in this assignment. You can assume that the system is being used by an Admin, who has full access to manage products, categories, and SKUs.

2. Entities & Relationships

· Entities

o Category: Used to group products (e.g., Electronics, Apparel).

o Product: Represents a general product concept (e.g., "iPhone 15").

o SKU: Represents a sellable variant of a product (e.g., "iPhone 15 - 128GB - Black").

· Relationships

o A Product belongs to one Category.

o A Product can have many SKUs.

o A SKU belongs to one Product.

3. Requirements

3.1 Build Rest APIs for

· Category

o Create, Read, Update, Delete Categories

o List all categories

· Product

o Create, Read, Update, Delete Products

o List Products with:

§ Search by product name

§ Filter by category

§ Pagination (page & pageSize params)

o Each Product must belong to an existing Category

· SKU

o Add, Update, Delete SKUs for a Product

o Each SKU must belong to a valid Product

o Return all SKUs of a product

3.1.1 Category Management
  - Category names must be unique.
  - Categories support one-level nesting via a parentCategoryId field.
  - When deleting a category with sub-categories or products, the API must warn and require confirmation before recursive deletion of all children and products.
  - No descriptions or images for categories.

3.1.2 Product Management
  - Product attributes: name, description (max 500 chars, HTML allowed), brand (from managed list), active/inactive status.
  - Each product belongs to one category.
  - Inactive products are excluded from listings but available via direct API calls.
  - API to manage brands (create, update, delete, list).

3.1.3 SKU Management
  - SKU attributes: price, color, size (from allowed values list).
  - SKUs inherit images from the product; if no product image, use a default image URL.
  - No inventory tracking per SKU.
  - No APIs to manage allowed values for color/size; these are fixed lists.

3.1.4 API Details
  - All APIs follow RESTful conventions (HTTP verbs, status codes).
  - Endpoints use versioning: /api/v1/
  - All responses use a standard structure: { success, data, error }.
  - Response format is JSON.

3.1.5 Validation & Edge Cases
  - Products cannot be created with non-existent categories.
  - Deleting a category/product/SKU deletes all related entities recursively, with confirmation required.
  - Deletion actions are logged for audit (user, timestamp, entity type, operation).
  - Bulk operations (e.g., bulk delete) are supported for categories, products, SKUs; limits per request should be defined by implementation.

3.1.6 Testing
  - Minimum code coverage: 80%, target 100%.
  - Unit tests only, using gtest framework.
  - Coverage report must be included in the repository, preferably in JSON format (coverage.py or similar).

3.2 Expectation

· The code should be of production grade.

· Handle all the necessary validations, relationships, edge cases.

· Write Unit tests and share the coverage report.

· ensure code-quality, code-structure, API documentation, complete test coverage.