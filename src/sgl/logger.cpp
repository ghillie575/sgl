#include <sgl/logger.h>
#include <iostream>

#if defined(_WIN32)
#include <windows.h>
#endif

Logger* logger = new Logger(); // Global instance
bool debugMode = false;

Logger::Logger() {
#if defined(_WIN32)
    // Enable ANSI escape codes on Windows 10+
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
#endif
}

Logger* getLogger() {
    return logger;
}

// ANSI escape codes for colors
const std::string RESET  = "\033[0m";
const std::string RED    = "\033[31m";
const std::string YELLOW = "\033[33m";
const std::string GREEN  = "\033[32m";
const std::string CYAN   = "\033[36m";
const std::string WHITE  = "\033[37m";

void Logger::log(const std::string& className, const std::string& message) {
    std::cout << GREEN << "[INFO]" << RESET << "[" << CYAN << className << RESET << "]: " << message << std::endl;
}

void Logger::warn(const std::string& className, const std::string& message) {
    std::cout << YELLOW << "[WARN]" << RESET << "[" << CYAN << className << RESET << "]: " << message << std::endl;
}

void Logger::error(const std::string& className, const std::string& message) {
    std::cout << RED << "[ERROR]" << RESET << "[" << CYAN << className << RESET << "]: " << message << std::endl;
}

void Logger::debug(const std::string& className, const std::string& message) {
    if (!debugMode) return;
    std::cout << WHITE << "[DEBUG]" << RESET << "[" << CYAN << className << RESET << "]: " << message << std::endl;
}

void setDebugMode(bool mode) {
    debugMode = mode;
}

