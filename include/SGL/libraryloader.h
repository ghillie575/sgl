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

namespace SGL {
namespace fs = std::filesystem;

class Window; // Forward declaration of the Window class

/**
 * @brief Enum representing the type of library.
 */
enum LibType {
    OBJECT,    ///< Represents an object library.
    COMPONENT, ///< Represents a component library.
    WINDOW,    ///< Represents a window library.
    GENERAL    ///< Represents a general-purpose library.
};

/**
 * @brief Class to store information about a library.
 */
class LibInfo {
public:
    /**
     * @brief Constructor to initialize library information.
     * @param id The unique identifier of the library.
     * @param info Additional information about the library.
     * @param type The type of the library.
     */
    LibInfo(const std::string& id, const std::string& info, LibType type) : id(id), info(info), type(type) {}

    /**
     * @brief Default constructor.
     */
    LibInfo() {}

    std::string id;   ///< Unique identifier of the library.
    std::string info; ///< Additional information about the library.
    LibType type;     ///< Type of the library.
};

/**
 * @brief Class representing a dynamically loaded library.
 */
class SGLLibrary {
public:
    /**
     * @brief Constructor to initialize the library with its file path.
     * @param path The file path of the library.
     */
    SGLLibrary(const std::string& path) : path(path) {}

    /**
     * @brief Opens the library for dynamic loading.
     */
    void open();

    /**
     * @brief Closes the dynamically loaded library.
     */
    void close();

    /**
     * @brief Retrieves a function pointer from the library.
     * @param funcName The name of the function to retrieve.
     * @return A pointer to the requested function.
     */
    void* getFunction(const char* funcName);

    std::string path; ///< File path of the library.
    LibInfo info;     ///< Information about the library.

private:
    void* handle; ///< Handle to the dynamically loaded library.
    Logger logger = Logger("LibraryLoader"); ///< Logger for logging library operations.
};

/**
 * @brief Class to manage the loading and handling of multiple libraries.
 */
class LibraryLoader {
public:
    /**
     * @brief Constructor to initialize the library loader with a directory.
     * @param directory The directory containing the libraries to load.
     */
    explicit LibraryLoader(const std::string& directory);

    /**
     * @brief Loads libraries and registers them with the given window.
     * @param window Pointer to the window instance.
     */
    void loadLibraries(Window* window);

    /**
     * @brief Loads libraries from a specified directory and registers them with the given window.
     * @param window Pointer to the window instance.
     * @param dirPath The directory path to load libraries from.
     */
    void loadLibraries(Window* window, std::string dirPath);

    /**
     * @brief Executes type registration for the loaded libraries on the given window.
     * @param window Pointer to the window instance.
     */
    void executeOnTypeRegister(Window* window);

private:
    std::string libraryDirectory; ///< Directory containing the libraries.
    Logger logger; ///< Logger for logging library loader operations.
    std::vector<std::unique_ptr<SGLLibrary>> libraries; ///< List of loaded libraries.

    /**
     * @brief Loads a single library from the specified path.
     * @param libPath The file path of the library to load.
     */
    void loadLibrary(const std::string& libPath);

    /**
     * @brief Checks if a file is a valid library file.
     * @param path The file path to check.
     * @return True if the file is a valid library, false otherwise.
     */
    bool isLibraryFile(const fs::path& path);
};

} // namespace SGL

#endif // LIBRARYLOADER_H
