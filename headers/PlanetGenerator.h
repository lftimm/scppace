#pragma once

#include "Planet.h"
#include <raymath.h>

class PlanetGenerator 
{
private:
    double m_min_radius{0};
    double m_max_radius{};
    
    double m_min_mass{0};
    double m_max_mass{};

    double m_min_x{0};
    double m_max_x{1};

    double m_min_y{0};
    double m_max_y{1};

    double m_min_z{};
    double m_max_z{};

public:
    PlanetGenerator& withMass(double min, double max);
    PlanetGenerator& withRadius(double min, double max);
    PlanetGenerator& withXIn(double min, double max);
    PlanetGenerator& withYIn(double min, double max);

    Planet generate();
};
