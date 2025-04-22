#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

namespace SGL {

/**
 * @brief Enum representing different log levels.
 */
enum LogLevel {
    INFO,   ///< Informational messages
    WARN,   ///< Warning messages
    ERROR,  ///< Error messages
    DEBUG   ///< Debug messages
};

/**
 * @brief A simple logger class for logging messages with different log levels.
 */
class Logger {
public:
    bool debug = false; ///< Flag to enable or disable debug messages.

    /**
     * @brief Constructs a Logger with a specific class name.
     * @param className The name of the class using the logger.
     */
    Logger(const std::string &className) : className(className) {}

    /**
     * @brief Constructs a Logger with a specific class name and debug flag.
     * @param className The name of the class using the logger.
     * @param debug Flag to enable or disable debug messages.
     */
    Logger(const std::string &className, bool debug) : className(className) {
        this->debug = debug;
    }

    /**
     * @brief Default constructor for Logger.
     */
    Logger() = default;

    /**
     * @brief Logs a message with a specified log level.
     * @param level The log level (INFO, WARN, ERROR, DEBUG).
     * @param message The message to log.
     */
    void log(LogLevel level, const std::string &message) {
        std::string levelStr;
        switch (level) {
        case INFO:
            levelStr = "\e[94mINFO\e[0m";
            break;
        case WARN:
            levelStr = "\e[93mWARN\e[0m";
            break;
        case ERROR:
            levelStr = "\e[91mERROR\e[0m";
            break;
        case DEBUG:
            if (!debug) return;
            levelStr = "\e[90mDEBUG\e[0m";
            break;
        }
        std::cout << "[\e[92m" << className << "\e[0m] [" << levelStr << "] " << message << std::endl;
    }

private:
    std::string className = ""; ///< The name of the class using the logger.
};

} // namespace SGL

#endif