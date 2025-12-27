#pragma once

#include "Planet.h"
#include <vector>

namespace Scenes 
{
    enum Scene {
        ThreeBody,
        BlackHole,
        FreeScene,
    };

    std::vector<Planet> threeBody();
    std::vector<Planet> blackHole();
    std::vector<Planet> freeScene();
    std::vector<Planet> next(Scene scene);
}

