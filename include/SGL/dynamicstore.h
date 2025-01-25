#include <map>
#include <string>
#include <typeinfo>
#include <SGL/object.h>
namespace SGL{
class DynamicStore {
public:
    GameObject get_object(const std::string& name);
private:
    
};
}