#include <iostream>
#include <transform.h>
#include <object.h>
class Component {
public:
    Transform* Transform;
    GameObject * GameObject;
    void Start();
    void Update();
    void setProprety();
};