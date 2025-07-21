
#include "AuditLogger.h"
#include <chrono>
#include <ctime>
#include <filesystem>
#include <mutex>

void AuditLogger::close() {
    std::lock_guard<std::mutex> lock(mtx);
    if (logFile.is_open()) logFile.close();
}

AuditLogger& AuditLogger::getInstance() {
    static AuditLogger instance;
    return instance;
}

AuditLogger::AuditLogger() {
    openLogFile();
}

void AuditLogger::openLogFile() {
    std::filesystem::create_directories("logs");
    if (!std::filesystem::exists("logs/audit.log")) {
        std::ofstream createFile("logs/audit.log");
        createFile.close();
    }
    currentLogFileName = "logs/audit.log";
    logFile.open(currentLogFileName, std::ios::app);
}

std::string AuditLogger::getTimestamp() const {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    char buf[32];
    // Windows: use localtime_s for thread safety
    struct tm timeinfo;
    localtime_s(&timeinfo, &now_c);
    std::strftime(buf, sizeof(buf), "%Y-%m-%d_%H-%M-%S", &timeinfo); // Windows-safe
    return buf;
}

void AuditLogger::log(const std::string& user, const std::string& entity, const std::string& operation) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!logFile.is_open()) openLogFile();
    logFile << getTimestamp() << " | " << user << " | " << entity << " | " << operation << std::endl;
}

void AuditLogger::rotateLogs() {
    std::lock_guard<std::mutex> lock(mtx);
    logFile.close();
    std::filesystem::create_directories("logs");
    if (!std::filesystem::exists(currentLogFileName)) {
        std::ofstream createFile(currentLogFileName);
        createFile.close();
    }
    std::string rotatedName = "logs/audit_" + getTimestamp() + ".log";
    std::filesystem::rename(currentLogFileName, rotatedName);
    openLogFile();
}

void AuditLogger::cleanupOldLogs(int days) {
    namespace fs = std::filesystem;
    fs::create_directories("logs");
    if (!fs::exists("logs")) {
        fs::create_directory("logs");
    }
    auto now = std::chrono::system_clock::now();
    for (const auto& entry : fs::directory_iterator("logs")) {
        if (entry.is_regular_file()) {
            auto ftime = fs::last_write_time(entry);
            // Convert file_time_type to system_clock::time_point
            auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                ftime - decltype(ftime)::clock::now() + std::chrono::system_clock::now());
            auto age = std::chrono::duration_cast<std::chrono::hours>(now - sctp).count() / 24;
            if (age > days) fs::remove(entry);
        }
    }
}
