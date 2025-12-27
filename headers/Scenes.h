#pragma once

#include "Planet.h"
#include <vector>

namespace Scenes 
{
    enum Scene {
        BlackHole = 0,
        ThreeBody = 1,
        FreeScene = 2,
    };

    std::vector<Planet> threeBody();
    std::vector<Planet> blackHole();
    std::vector<Planet> freeScene();
    std::vector<Planet> next(Scene scene);
}

