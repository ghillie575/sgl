#ifndef LAYOUTDATA_H
#define LAYOUTDATA_H

#include <vector>
#include <algorithm>
#include <SGL/LayoutManaging/layoutobject.h> // For std::remove

namespace SGL::LayoutManaging {

class LayoutData {
public:
    LayoutData();
    ~LayoutData();

    void addObject(LayoutObject* object);
    void removeObject(LayoutObject* object);
    LayoutObject* getObject(int index);
    int getObjectCount() const;
private:
    std::vector<LayoutObject*> objects_;
};

} // namespace SGL::LayoutManaging

#endif // LAYOUTDATA_H