# Technical PRD

**Backend Language & Framework:**
- C++ using CppRestSDK

**Data Storage:**
- Local filesystem, organized per entity (categories.json, products.json, skus.json)
- Backup/restore mechanism for data files

**Deployment & Infrastructure:**
- AWS EC2 instances
- Automated deployment via AWS CodePipeline
- No scalability/HA/disaster recovery required

**Configuration:**
- Brands, colors, sizes, default image URL loaded at startup via environment variables

**API:**
- RESTful endpoints, versioned as `/api/v1/`
- Auto-generated Swagger documentation at `/api/v1/docs`
- Standard response structure: `{ success, data, error }`
- JSON format only
- Synchronous bulk operations

**Audit Logging:**
- Log file storage with automatic rotation, retention up to 30 days

**Testing & CI/CD:**
- Unit tests using gtest
- Minimum 80% code coverage, target 100%
- Coverage report in repository (JSON format)
- Automated tests in CI/CD pipeline

**Error Handling:**
- API responses include brief error descriptions only
