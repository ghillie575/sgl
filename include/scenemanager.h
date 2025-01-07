#include <iostream>
#include <window.h>
#include <scenedata.h>
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
void loadScene(Window* window, const std::string& json);
void loadSceneByName(Window* window, const std::string& sceneName);
std::string createScene(SceneData* data);
void saveScene(SceneData* data, const std::string& sceneName);
#endif