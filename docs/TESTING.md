# Testing & Coverage

- All modules have unit tests (see `/tests`)
- Build and run tests:
  ```sh
  mkdir build && cd build
  cmake ..
  cmake --build .
  ./UnitTests
  ```
- Coverage report generated via gcov/lcov (see `/coverage`)
- Minimum coverage: 80%, target: 100%
