#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <string>
class Logger
{
public:
    std::string classname;
    Logger(std::string classname) : classname(classname) {}
    enum class Level
    {
        INFO,
        WARNING,
        ERROR
    };
    void log(const std::string &message, Level level = Level::INFO)
    {
        switch (level)
        {
        case Level::INFO:
            std::cout <<  "[" << classname << " ] " << "[INFO] " << message << std::endl;
            break;
        case Level::WARNING:
            std::cout <<  "[" << classname << " ] " << "[WARNING] " << message << std::endl;
            break;
        case Level::ERROR:
            std::cerr <<  "[" << classname << " ] " << "[ERROR] " << message << std::endl;
            break;
        }
    }
};
#endif