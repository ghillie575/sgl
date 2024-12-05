#include <iostream>
#include <window.h>
#include <scenedata.h>
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
void loadScene(Window* window,std::string json);
std::string createScene(SceneData* data);
#endif