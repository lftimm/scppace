#include "PlanetGenerator.h"

#include <random>
#include "Consts.h"

PlanetGenerator& PlanetGenerator::withMass(double min, double max) { 

    m_min_mass = min;
    m_max_mass = max;

    return *this;
}

PlanetGenerator& PlanetGenerator::withRadius(double min, double max) { 

    m_min_radius = min;
    m_max_radius = max;

    return *this;
}


PlanetGenerator& PlanetGenerator::withXIn(double min, double max) {

    m_min_x = Consts::getXAtWindowPercent(min);
    m_max_x = Consts::getXAtWindowPercent(max);
    
    return *this;
}

PlanetGenerator& PlanetGenerator::withYIn(double min, double max) {

    m_min_y = Consts::getYAtWindowPercent(min);
    m_max_y = Consts::getYAtWindowPercent(max);
    
    return *this;

}

float generateRandomValue(float min, float max) {

    static std::random_device dev;
    static std::mt19937 rng(dev());

    std::uniform_real_distribution<float> dist(min, max);

    return dist(rng);
}

Planet PlanetGenerator::generate() {

    float mass = generateRandomValue(m_min_mass, m_max_mass);
    float radius = generateRandomValue(m_min_radius, m_max_radius);
    float x = generateRandomValue(m_min_x, m_max_x);
    float y = generateRandomValue(m_min_y, m_max_y);
    float z = generateRandomValue(m_min_z, m_max_z);

    Vector3 pos{x,y,z};
    return Planet(
        pos,
        radius,
        mass
    );
}
