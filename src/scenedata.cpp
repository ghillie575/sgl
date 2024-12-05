#include <scenedata.h>

    SceneData::SceneData() {}
    SceneData::~SceneData() {
    }

    void SceneData::addObject(SceneObject* object) {
        objects_.push_back(object);
    }

    void SceneData::removeObject(SceneObject* object) {
        auto it = std::find(objects_.begin(), objects_.end(), object);
        if (it != objects_.end()) {
            objects_.erase(it);
        }
    }

    SceneObject* SceneData::getObject(int index) {
        if (index >= 0 && index < objects_.size()) {
            return objects_[index];
        }
        return nullptr;
    }

    int SceneData::getObjectCount() {
        return objects_.size();
    }
