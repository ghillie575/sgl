#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
namespace SGL{
enum LogLevel
{
    INFO,
    WARN,
    ERROR,
    DEBUG
};
class Logger
{
public:
    bool debug = false;
    Logger(const std::string &className) : className(className) {}
    Logger(const std::string &className,bool debug) : className(className) {
        this->debug = debug;
    }
    Logger() = default;

    void log(LogLevel level, const std::string &message)
    {
        std::string levelStr;
        switch (level)
        {
        case INFO:
            levelStr = "\e[94minfo\e[0m";
            break;
        case WARN:
            levelStr = "\e[93mwarn\e[0m";
            break;
        case ERROR:
            levelStr = "\e[91merror\e[0m";
            break;
        case DEBUG:
            if(!debug) return;
            levelStr = "\e[90mDEBUG\e[0m";
            break;
        }
        std::cout << "[\e[92m" << className << "\e[0m] [" << levelStr << "] " << message << std::endl;
    }

private:
    std::string className = "";
    
};
}
#endif