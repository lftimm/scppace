#pragma once

#include <string>

namespace Cts
{
    constexpr float gravity{9.81*100};
    constexpr int height{1000};
    constexpr int width{1600};
    constexpr const char* title{"scppace"};

    constexpr float getXAtWindowPercent(const float percentage) {
        return height * percentage;
    }

    constexpr float getYAtWindowPercent(const float percentage) {
        return width * percentage;
    }
}
