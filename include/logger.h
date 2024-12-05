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
            levelStr = "info";
            break;
        case WARN:
            levelStr = "warn";
            break;
        case ERROR:
            levelStr = "error";
            break;
        }
        std::cout << "[" << className << "] [" << levelStr << "] " << message << std::endl;
    }

private:
    std::string className;
};
#endif