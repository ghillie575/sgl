#include <SGL/libraryloader.h>
#include <stdexcept>
#include <iostream>

LibraryLoader::LibraryLoader(const std::string& directory)
    : libraryDirectory(directory), logger("LibraryLoader") {}

void LibraryLoader::loadLibraries(Window* window)
{
    logger.debug = window->debug;
    logger.log(LogLevel::INFO, "Scanning directory: " + libraryDirectory);

    for (const auto& entry : fs::directory_iterator(libraryDirectory))
    {
        if (entry.is_regular_file() && isLibraryFile(entry.path()))
        {
            try
            {
                loadLibrary(entry.path().string());
            }
            catch (const std::exception& e)
            {
                logger.log(LogLevel::ERROR, "Error loading library " + entry.path().string() + ": " + e.what());
            }
        }
    }
    logger.log(LogLevel::INFO, "Finished loading libraries.");
}

void LibraryLoader::loadLibrary(const std::string& libPath)
{
    auto lib = std::make_unique<DynamicLibrary>(libPath);
    logger.log(LogLevel::INFO, "Loaded file: " + libPath);
    libraries.push_back(std::move(lib));
}

void LibraryLoader::executeOnTypeRegister(Window* window)
{
    for (auto& lib : libraries)
    {
        try
        {
            logger.log(LogLevel::DEBUG, "Looking for onTypeRegister in library: " + lib->path);
            auto onTypeRegister = reinterpret_cast<void (*)(Window*)>(lib->getFunction("onTypeRegister"));
            logger.log(LogLevel::DEBUG, "Executing onTypeRegister for library: " + lib->path);
            onTypeRegister(window);
            logger.log(LogLevel::INFO, "Loaded types for: " + lib->path);
        }
        catch (const std::exception& e)
        {
            logger.log(LogLevel::ERROR, "Error executing onTypeRegister: " + std::string(e.what()));
        }
    }
}

bool LibraryLoader::isLibraryFile(const fs::path& path)
{
#if defined(_WIN32) || defined(_WIN64)
    return path.extension() == ".dll";
#else
    return path.extension() == ".so" || path.extension() == ".dylib";
#endif
}

LibraryLoader::DynamicLibrary::DynamicLibrary(const std::string& libPath)
{
#if defined(_WIN32) || defined(_WIN64)
    handle = LoadLibrary(libPath.c_str());
    if (!handle)
        throw std::runtime_error("Failed to load library: " + libPath);
#else
    handle = dlopen(libPath.c_str(), RTLD_LAZY | RTLD_GLOBAL);
    if (!handle)
        throw std::runtime_error(dlerror());
#endif
    path = libPath;
}

LibraryLoader::DynamicLibrary::~DynamicLibrary()
{
#if defined(_WIN32) || defined(_WIN64)
    if (!handle)
        FreeLibrary(static_cast<HMODULE>(handle));
#else
    if (!handle)
        dlclose(handle);
#endif
}

void* LibraryLoader::DynamicLibrary::getFunction(const char* funcName)
{
#if defined(_WIN32) || defined(_WIN64)
    void* func = GetProcAddress(static_cast<HMODULE>(handle), funcName);
#else
    void* func = dlsym(handle, funcName);
#endif
    if (!func)
        throw std::runtime_error("Failed to load function: " + std::string(funcName) + " from " + path);
    return func;
}
