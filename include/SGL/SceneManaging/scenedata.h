#include <SGL/SceneManaging/sceneobject.h>
#include<vector>
#ifndef SCENEDATA_H
#define SCENEDATA_H
namespace SGL{
class SceneData {
public:
    SceneData();
    ~SceneData();

    void addObject(SceneObject* object);
    void removeObject(SceneObject* object);
    SceneObject* getObject(int index);
    int getObjectCount();

private:
    std::vector<SceneObject*> objects_;
};
}
#endif // SCENEDATA_H