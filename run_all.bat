@echo off
REM Build the project
cmake --build . --config Debug
IF %ERRORLEVEL% NEQ 0 (
    echo Build failed.
    exit /b %ERRORLEVEL%
)

REM Run unit tests
Debug\UnitTests.exe
IF %ERRORLEVEL% NEQ 0 (
    echo Unit tests failed.
    exit /b %ERRORLEVEL%
)

REM Generate code coverage report
OpenCppCoverage --sources src\main.cpp --sources src\ConfigLoader.cpp --sources src\CategoryHandler.cpp --sources src\ProductHandler.cpp --sources src\SKUHandler.cpp --sources src\AuditLogger.cpp --sources src\ProductController.cpp --sources src\ProductService.cpp --export_type=html:coverage_html -- Debug\UnitTests.exe
IF %ERRORLEVEL% NEQ 0 (
    echo Code coverage generation failed.
    exit /b %ERRORLEVEL%
)

echo All steps completed successfully.
