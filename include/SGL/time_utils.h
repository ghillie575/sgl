#ifndef TIME_H
#define TIME_H
namespace SGL{
class Time {
private:
    float deltaTime = 0;

public:
    inline float getDeltaTime() const { return deltaTime; }
    inline void setDeltaTime(float deltaTimeI) { deltaTime = deltaTimeI; }
};
}
#endif
