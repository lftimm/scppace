#include <functional>
#include <unordered_map>
#include <vector>

#include "Scenes.h"
#include "Planet.h"
#include "PlanetGenerator.h"
#include "Consts.h"

using sceneFactory = std::function<std::vector<Planet>()>;
static std::unordered_map<Scenes::Scene, sceneFactory> sceneMap{
    {Scenes::BlackHole, Scenes::blackHole},
    {Scenes::ThreeBody, Scenes::threeBody},
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

    for(int i = 0 ; i < 2000; i++)
    {
        Planet randomPlanet = generator.generate();
        Vector3 pos{randomPlanet.position()};
        float angle{atanf(pos.y/pos.x)};
        randomPlanet.speed = Vector3{100*cos(angle),-100*sin(angle),0};
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
    std::vector<Planet> planets{};

    PlanetGenerator generator;
    generator
        .withMass(50, 100)
        .withRadius(40, 60)
        ;

    generator.withXIn(0.15, 0.45).withYIn(0.5, 0.75);
    planets.push_back(
            generator.generate()
    );

    generator.withXIn(0.55, 0.85).withYIn(0.5, 0.75);
    planets.push_back(
            generator.generate()
    );

    generator.withXIn(0.45, 0.55).withYIn(0, 1);
    planets.push_back(
            generator.generate()
    );
    
    return planets;
}

std::vector<Planet> Scenes::freeScene() {
    return std::vector<Planet>();
}
