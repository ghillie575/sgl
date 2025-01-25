#include <iostream>
#include <SGL/window.h>
#include <SGL/scenedata.h>
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
namespace SGL{
void loadScene(Window* window, const std::string& json);
void loadSceneByName(Window* window, const std::string& sceneName);
std::string createScene(SceneData* data);
void saveScene(SceneData* data, const std::string& sceneName);
}
#endif