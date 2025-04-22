#ifndef TIME_H
#define TIME_H

// Namespace for the Simple Graphics Library (SGL)
namespace SGL {

/**
 * @brief A class to manage and provide time-related utilities.
 * 
 * The Time class is used to store and retrieve the delta time, 
 * which represents the time elapsed between frames or updates.
 */
class Time {
private:
    float deltaTime = 0; ///< The time elapsed between frames or updates.

public:
    /**
     * @brief Get the delta time.
     * 
     * @return The current delta time.
     */
    inline float getDeltaTime() const { return deltaTime; }

    /**
     * @brief Set the delta time.
     * 
     * @param deltaTimeI The new delta time to set.
     */
    inline void setDeltaTime(float deltaTimeI) { deltaTime = deltaTimeI; }
};

} // namespace SGL

#endif // TIME_H
