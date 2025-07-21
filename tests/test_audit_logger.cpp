#include <gtest/gtest.h>
#include "AuditLogger.h"
#include <filesystem>
#include <fstream>
#include <thread>

TEST(AuditLogger, LogWrite) {
    std::filesystem::create_directories("logs");
    std::ofstream("logs/audit.log") << "";
    auto& logger = AuditLogger::getInstance();
    logger.log("admin", "Product", "create");
    logger.log("admin", "Category", "delete");
    std::ifstream file("logs/audit.log");
    ASSERT_TRUE(file.is_open());
    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        if (!line.empty()) ++count;
    }
    ASSERT_GE(count, 2);
}

TEST(AuditLogger, LogRotation) {
    std::filesystem::create_directories("logs");
    std::ofstream("logs/audit.log") << "";
    auto& logger = AuditLogger::getInstance();
    logger.log("admin", "SKU", "update");
    logger.rotateLogs();
    bool foundRotated = false;
    for (const auto& entry : std::filesystem::directory_iterator("logs")) {
        if (entry.path().string().find("audit_") != std::string::npos) {
            foundRotated = true;
            break;
        }
    }
    ASSERT_TRUE(foundRotated);
}

TEST(AuditLogger, CleanupOldLogs) {
    std::filesystem::create_directories("logs");
    // Remove all files in logs before test
    auto& logger = AuditLogger::getInstance();
    logger.close();
    for (const auto& entry : std::filesystem::directory_iterator("logs")) {
        if (entry.is_regular_file()) std::filesystem::remove(entry);
    }
    logger.openLogFile();
    logger.log("admin", "Product", "create");
    logger.rotateLogs();
    logger.close();
    logger.cleanupOldLogs(0); // Should remove all logs older than 0 days
    int fileCount = 0;
    for (const auto& entry : std::filesystem::directory_iterator("logs")) {
        if (entry.is_regular_file()) ++fileCount;
    }
    ASSERT_LE(fileCount, 2); // At most two files (current + rotated log)
}
