#include "Logger.h"

Logger& Logger::Instance()
{
     static Logger instance; // Singleton instance, initialized once
     return instance;
}


void Logger::LOGS(const std::string& message) {
    logs.push_back(message);
}

void Logger::Clear() {
    logs.clear();
}

const std::vector<std::string>& Logger::GetLogs() const {
    return logs;
}