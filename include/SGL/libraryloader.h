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
enum LibType{
    OBJECT,
    COMPONENT,
    WINDOW,
    GENERAL
};
class LibInfo{

public:
    LibInfo(const std::string& id, const std::string& info, LibType type) : id(id), info(info), type(type) {};
    LibInfo() {};
    std::string id;
    std::string info;
    LibType type;
};
class SGLLibrary{

public:
    SGLLibrary(const std::string& path) : path(path) {};
    LibInfo info;
    void open();
    void close();
    void* getFunction(const char* funcName);
    std::string path;
private:
    void* handle;
    Logger logger = Logger("LibraryLoader");
};
class LibraryLoader
{
public:
    explicit LibraryLoader(const std::string& directory);

    void loadLibraries(Window* window);
    void loadLibraries(Window* window,std::string dirPath);
    void executeOnTypeRegister(Window* window);
private:
    std::string libraryDirectory;
    Logger logger;
    std::vector<std::unique_ptr<SGLLibrary>> libraries;
    
    void loadLibrary(const std::string& libPath);

    bool isLibraryFile(const fs::path& path);
};

#endif // LIBRARYLOADER_H
