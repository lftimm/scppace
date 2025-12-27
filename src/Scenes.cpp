#include <functional>
#include <vector>

#include "Scenes.h"
#include "PlanetGenerator.h"
#include "Consts.h"

using sceneFactory = std::function<std::vector<Planet>()>;
static std::unordered_map<Scenes::Scene, sceneFactory> sceneMap{
        {Scenes::ThreeBody, Scenes::threeBody},
       {Scenes::BlackHole, Scenes::blackHole},
        {Scenes::FreeScene, Scenes::freeScene},
};

std::vector<Planet> Scenes::next(Scene scene)
{
    return sceneMap.at(scene)();
}

std::vector<Planet> Scenes::blackHole() {
    
    std::vector<Planet> planets{};
    PlanetGenerator generator;

    generator
        .withMass(0.05, 0.1)
        .withRadius(5, 10)
        .withXIn(0.25, 0.75)
        .withYIn(0, 1)
        ;

    for(int i = 0 ; i < 100; i++)
    {
        Planet randomPlanet = generator.generate();
        randomPlanet.speed = Vector3{1000,1000,0};
        planets.push_back(randomPlanet);
    }

    planets.push_back(Planet{
        Consts::getXAtWindowPercent(0.5),
        Consts::getYAtWindowPercent(0.5),
        100,
        1e3
    });

    return planets;
}

std::vector<Planet> Scenes::threeBody() {
    return std::vector<Planet>();
}

std::vector<Planet> Scenes::freeScene() {
    return std::vector<Planet>();
}
