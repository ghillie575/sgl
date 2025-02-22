#include <SGL/LayoutManaging/layoutdata.h>
using namespace SGL::LayoutManaging;
    LayoutData::LayoutData() {}
    LayoutData::~LayoutData() {
    }

    void LayoutData::addObject(LayoutObject* object) {
        objects_.push_back(object);
    }

    void LayoutData::removeObject(LayoutObject* object) {
        auto it = std::find(objects_.begin(), objects_.end(), object);
        if (it != objects_.end()) {
            objects_.erase(it);
        }
    }

    LayoutObject* LayoutData::getObject(int index) {
        if (index >= 0 && index < objects_.size()) {
            return objects_[index];
        }
        return nullptr;
    }

    int LayoutData::getObjectCount() const {
        return objects_.size();
    }
