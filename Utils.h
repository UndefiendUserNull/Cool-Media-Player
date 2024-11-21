#pragma once
#include <string>

namespace Utils
{
    std::string formatTime(const float timeInSeconds)
    {
        int mins{(int) floor(timeInSeconds / 60)};
        int remSeconds = {(int) (floor(timeInSeconds)) % 60};

        return std::to_string(mins) + ":" + (remSeconds < 10 ? "0" : "") + std::to_string(remSeconds);
    }
}
