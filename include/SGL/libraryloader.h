#ifndef LIBRARYLOADER_H
#define LIBRARYLOADER_H

#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include <SGL/window.h> 

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include <SGL/logger.h>

namespace fs = std::filesystem;
class Window;
class LibraryLoader
{
public:
    explicit LibraryLoader(const std::string& directory);

    void loadLibraries(Window* window);
    void executeOnTypeRegister(Window* window);
private:
    struct DynamicLibrary
    {
        std::string path;
        void* handle;

        explicit DynamicLibrary(const std::string& libPath);
        ~DynamicLibrary();
        void* getFunction(const char* funcName);
    };

    std::string libraryDirectory;
    Logger logger;
    std::vector<std::unique_ptr<DynamicLibrary>> libraries;

    void loadLibrary(const std::string& libPath);
    
    bool isLibraryFile(const fs::path& path);
};

#endif // LIBRARYLOADER_H
