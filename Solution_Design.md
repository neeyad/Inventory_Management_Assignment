# Solution Design

## Modules
1. **API Layer:**
   - CppRestSDK controllers for Category, Product, SKU, Brand
   - Handles REST endpoints, request validation, response formatting

2. **Service Layer:**
   - Business logic for CRUD, bulk operations, validation, confirmation flows

3. **Data Layer:**
   - JSON file read/write for each entity
   - Backup/restore utilities

4. **Config Loader:**
   - Loads environment variables at startup

5. **Audit Logger:**
   - Writes actions to log file, manages rotation and retention

6. **Swagger Integration:**
   - Generates and serves API docs

7. **Testing:**
   - gtest-based unit tests for all modules

8. **CI/CD Pipeline:**
   - AWS CodePipeline for build, test, deploy
