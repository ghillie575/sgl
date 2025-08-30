#include <SGL/log_writter.h>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <chrono>
#include <iomanip>
namespace fs = std::filesystem;
SGL::LogWritter *logWritterInstance = new SGL::LogWritter();
namespace SGL
{

    void LogWritter::log(const std::string &message)
    {
        if (logFile.is_open())
        {
            logFile << message << std::endl;
        }
        else
        {
            std::cerr << "Unable to open log file." << std::endl;
        }
    }

    void LogWritter::init()
    {
        const std::string latestLogPath = "engine/logs/latest.log";

        // If latest.log exists, rename it
        if (fs::exists(latestLogPath))
        {
            std::ifstream oldLog(latestLogPath);
            std::string firstLine;
            if (oldLog.is_open() && std::getline(oldLog, firstLine))
            {
                // sanitize filename
                for (char &c : firstLine)
                {
                    if (c == '/' || c == '\\' || c == ':' || c == '*' ||
                        c == '?' || c == '"' || c == '<' || c == '>' || c == '|')
                    {
                        c = '_';
                    }
                }

                std::string newPath = "engine/logs/" + firstLine + ".log";

                // make unique if already exists
                int counter = 1;
                while (fs::exists(newPath))
                {
                    newPath = "engine/logs/" + firstLine + "_" + std::to_string(counter++) + ".log";
                }

                oldLog.close();
                fs::rename(latestLogPath, newPath);
            }
            else
            {
                oldLog.close();
                fs::remove(latestLogPath); // can't read, just remove
            }
        }

        // Now create a new latest.log
        logFile = std::ofstream(latestLogPath, std::ios_base::trunc);

        if (logFile.is_open())
        {
            // current datetime
            auto now = std::chrono::system_clock::now();
            std::time_t now_c = std::chrono::system_clock::to_time_t(now);

            logFile << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S") << std::endl;
            logFile << "Log started" << std::endl;
        }
        else
        {
            std::cerr << "Unable to open log file." << std::endl;
        }
    }

    LogWritter *getLogWritterInstance()
    {
        return logWritterInstance;
    }
}