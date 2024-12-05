#pragma once
#include <vector>
#include <string>

class Logger {

public:
    static Logger& Instance();

    void LOGS(const std::string& message);
    void Clear();
    const std::vector<std::string>& GetLogs() const;


private:
    std::vector<std::string> logs;
};