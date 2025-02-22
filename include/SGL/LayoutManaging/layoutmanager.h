#ifndef LAYOUTMANAGER_H
#define LAYOUTMANAGER_H
#include <SGL/window.h>
#include <SGL/LayoutManaging/layoutdata.h>
namespace SGL::LayoutManaging{
    void loadLayoutByName(std::string layoutName,Window* window);
    void loadLayout(const std::string& json,Window* window);
    void saveLayout(LayoutData* data, const std::string& layoutName);
    std::string createLayout(LayoutData* layout);
}
#endif // LAYOUTMANAGER_H