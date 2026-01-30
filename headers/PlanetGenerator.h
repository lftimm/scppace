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

    double m_speed_min_x{};
    double m_speed_max_x{};

    double m_speed_min_y{};
    double m_speed_max_y{};

public:
    PlanetGenerator& withMass(double min, double max);
    PlanetGenerator& withRadius(double min, double max);
    PlanetGenerator& withXIn(double min, double max);
    PlanetGenerator& withYIn(double min, double max);
    PlanetGenerator& withSpeedX(double min, double max);
    PlanetGenerator& withSpeedY(double min, double max);

    Planet generate();
};
