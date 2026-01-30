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
};

std::vector<Planet> Scenes::next(Scene scene)
{
    return sceneMap.at(scene)();
}

std::vector<Planet> Scenes::blackHole() {
    
    std::vector<Planet> planets{};
    PlanetGenerator generator;

    generator
        .withMass(0.05, 5)
        .withRadius(15, 30)
        .withXIn(-2,-10)
        .withYIn(-10,2)
        .withSpeedX(0, 400)
        .withSpeedY(0, 1e4)
        ;

    for(int i = 0 ; i < 3500; i++)
    {
        Planet randomPlanet = generator.generate();
        planets.push_back(randomPlanet);
    }
    

    Planet blackHole{
        Consts::getXAtWindowPercent(0),
        Consts::getYAtWindowPercent(0),
        100,
        1e5,
        Vector3Zero()
    };

    planets.push_back(blackHole);

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
