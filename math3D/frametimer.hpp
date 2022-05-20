#pragma once

#include <chrono>

class FrameTimer
{
private:
    std::chrono::steady_clock::time_point last;
public:
    FrameTimer()
    {
        using namespace std::chrono;

        last = steady_clock::now();
    }

    float Mark()
    {
        using namespace std::chrono;

        const auto old = last;
        last = steady_clock::now();
        duration<float> frameTime = last - old;

        return frameTime.count();
    }
};