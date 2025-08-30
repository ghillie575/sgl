#ifndef LOG_WRITTER_H
#define LOG_WRITTER_H
#include <string>
#include <iostream>
#include <fstream>
namespace SGL
{
    class LogWritter
    {
        private:
        std::ofstream logFile;
    public:
        void log(const std::string &message);
        void init();
    };
    LogWritter* getLogWritterInstance();
}

#endif // LOG_WRITTER_H
