#ifndef LOGGER_H
#define LOGGER_H
#include <SGL/log_writter.h>
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
    Logger(const std::string &className) : className(className) {
       if(className == "ENGINE") {
            this->className = "\e[95m" + className + "\e[0m";
        }else if (className == "GameObject") {
            this->className = "\e[33m" + className + "\e[0m";
        }
        else if (className == "SceneLoader") {
            this->className = "\e[34m" + className + "\e[0m";
        }
        else if (className == "TYPE") {
            this->className = "\e[35m" + className + "\e[0m";
        }
        else if (className == "SHADER_L") {
            this->className = "\e[31m" + className + "\e[0m";
        }
        else if (className == "LibraryLoader") {
            this->className = "\e[32m" + className + "\e[0m";
        }
        else {
            this->className = "\e[37m" + className + "\e[0m";
        }
    }

    /**
     * @brief Constructs a Logger with a specific class name and debug flag.
     * @param className The name of the class using the logger.
     * @param debug Flag to enable or disable debug messages.
     */
    Logger(const std::string &className, bool debug) : className(className) {
        this->debug = debug;
        // Remove bash color codes from className
        std::string cleanClassName;
        bool inEscape = false;
        for (char c : className) {
            if (c == '\e') {
            inEscape = true;
            }
            if (!inEscape) {
            cleanClassName += c;
            }
            if (inEscape && c == 'm') {
            inEscape = false;
            }
        }
        this->rawClassName = cleanClassName;
        if(className == "ENGINE") {
            this->className = "\e[95m" + className + "\e[0m";
        }else if (className == "GameObject") {
            this->className = "\e[33m" + className + "\e[0m";
        }
        else if (className == "SceneLoader") {
            this->className = "\e[34m" + className + "\e[0m";
        }
        else if (className == "TYPE") {
            this->className = "\e[35m" + className + "\e[0m";
        }
        else if (className == "SHADER_L") {
            this->className = "\e[31m" + className + "\e[0m";
        }
        else if (className == "LibraryLoader") {
            this->className = "\e[32m" + className + "\e[0m";
        }
        else {
            this->className = "\e[37m" + className + "\e[0m";
        }
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
        std::string rawLevelStr;
        switch (level) {
        case INFO:
            levelStr = "\e[94mINFO\e[0m";
            rawLevelStr = "INFO";
            break;
        case WARN:
            levelStr = "\e[30m\e[43mWARN\e[0m";
            rawLevelStr = "WARN";
            break;
        case ERROR:
            levelStr = "\e[30m\e[41mERROR\e[0m";
            rawLevelStr = "ERROR";
            break;
        case DEBUG:
            if (!debug) return;
            levelStr = "\e[90mDEBUG\e[0m";
            rawLevelStr = "DEBUG";
            break;
        }
        std::string final_output = "[\e[92m" + className + "\e[0m] [" + levelStr + "] " + message + "\n";
        std::string final_output_raw ="[" + rawClassName + "] [" + rawLevelStr + "] " + message + "\n";
        std::cout << final_output;std::cout.flush();
        getLogWritterInstance()->log(final_output_raw);
    }

private:
    std::string className = ""; ///< The name of the class using the logger.
    std::string rawClassName = "";//< The raw class name without color codes.
};

} // namespace SGL

#endif