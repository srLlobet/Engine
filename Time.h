#pragma once
#include <chrono>

class Timer {
public:
    Timer() : lastTime(std::chrono::high_resolution_clock::now()) {}

    float GetDeltaTime() {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        return deltaTime.count(); 
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
};