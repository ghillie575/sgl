#ifndef LAYOUTMANAGER_H
#define LAYOUTMANAGER_H

#include <SGL/window.h>
#include <SGL/LayoutManaging/layoutdata.h>

namespace SGL::LayoutManaging {

    /**
     * @brief Loads a layout by its name and applies it to the specified window.
     * 
     * @param layoutName The name of the layout to load.
     * @param window Pointer to the window where the layout will be applied.
     */
    void loadLayoutByName(std::string layoutName, Window* window);

    /**
     * @brief Loads a layout from a JSON string and applies it to the specified window.
     * 
     * @param json The JSON string containing the layout data.
     * @param window Pointer to the window where the layout will be applied.
     */
    void loadLayout(const std::string& json, Window* window);

    /**
     * @brief Saves the given layout data to a file with the specified layout name.
     * 
     * @param data Pointer to the layout data to save.
     * @param layoutName The name of the layout file to save to.
     */
    void saveLayout(LayoutData* data, const std::string& layoutName);

    /**
     * @brief Creates a layout from the given layout data and returns it as a JSON string.
     * 
     * @param layout Pointer to the layout data to convert.
     * @return A JSON string representing the layout.
     */
    std::string createLayout(LayoutData* layout);

}

#endif // LAYOUTMANAGER_H