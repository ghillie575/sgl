#include <iostream>
#include <SGL/window.h>
#include <SGL/SceneManaging/scenedata.h>

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

namespace SGL {

/**
 * @brief Loads a scene from a JSON file and initializes it in the given window.
 * 
 * @param window Pointer to the Window object where the scene will be loaded.
 * @param json The JSON string containing the scene data.
 */
void loadScene(Window* window, const std::string& json);

/**
 * @brief Loads a scene by its name and initializes it in the given window.
 * 
 * @param window Pointer to the Window object where the scene will be loaded.
 * @param sceneName The name of the scene to load.
 */
void loadSceneByName(Window* window, const std::string& sceneName);

/**
 * @brief Creates a new scene based on the provided SceneData.
 * 
 * @param data Pointer to the SceneData object containing the scene details.
 * @return A string representing the created scene (e.g., JSON or identifier).
 */
std::string createScene(SceneData* data);

/**
 * @brief Saves the given scene data to a file or storage with the specified name.
 * 
 * @param data Pointer to the SceneData object to save.
 * @param sceneName The name under which the scene will be saved.
 */
void saveScene(SceneData* data, const std::string& sceneName);

} // namespace SGL

#endif