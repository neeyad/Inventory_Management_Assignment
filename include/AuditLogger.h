#pragma once
#include <string>
#include <fstream>
#include <mutex>

class AuditLogger {
public:
    static AuditLogger& getInstance();
    void log(const std::string& user, const std::string& entity, const std::string& operation);
    void rotateLogs();
    void cleanupOldLogs(int days = 30);
    void close();
    void openLogFile();
private:
    AuditLogger();
    std::ofstream logFile;
    std::mutex mtx;
    std::string currentLogFileName;
    std::string getTimestamp() const;
};
