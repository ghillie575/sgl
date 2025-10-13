#include <sgl/logger.h>
#include <iostream>
Logger* logger = new Logger(); // Global instance
Logger::Logger() {}
Logger* getLogger() {
    return logger;
}
void Logger::log(const std::string& className,const std::string& message) {
    std::cout << "[INFO]" << "[" << className << "]: " << message << std::endl;
}
void Logger::warn(const std::string& className,const std::string& message) {
    std::cout << "[WARN]" << "[" << className << "]: " << message << std::endl;
}
void Logger::error(const std::string& className,const std::string& message) {
    std::cout << "[ERROR]" << "[" << className << "]: " << message << std::endl;
}