#pragma once

namespace Consts
{
    constexpr int height{1000};
    constexpr int width{1900};
    constexpr const char* title{"scppace"};

    constexpr float uniGConst{1e6};

    constexpr float getXAtWindowPercent(const float percentage) {
        return width * percentage;
    }

    constexpr float getYAtWindowPercent(const float percentage) {
        return height * percentage;
    }
}
