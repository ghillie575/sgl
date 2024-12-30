#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
enum LogLevel
{
    INFO,
    WARN,
    ERROR
};
class Logger
{
public:
    Logger(const std::string &className) : className(className) {}

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
        }
        std::cout << "[\e[92m" << className << "\e[0m] [" << levelStr << "] " << message << std::endl;
    }

private:
    std::string className;
};
#endif