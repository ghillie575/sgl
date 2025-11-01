#ifndef LOGGER_H
#define LOGGER_H
#include <string>
class Logger {
public:
    Logger();
    void log(const std::string& className,const std::string&  message);
    void warn(const std::string&  className,const std::string&  message);
    void error(const std::string&  className,const std::string&  message);
    void debug(const std::string&  className,const std::string&  message);
};
Logger* getLogger();
void setDebugMode(bool mode);
#endif