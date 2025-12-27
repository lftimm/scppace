#pragma once

#include <raylib.h>
#include <vector>
#include <raymath.h>

class Planet
{
public:
    Planet(double x, double y, double radius, double mass);
    Planet(Vector3 pos, double radius, double mass);

    Vector3 gravityAt(const Planet& other) const;
    Vector3 gravityAt(const Vector3 pos, double mass) const;

    Vector3 speed{};
    Vector3 position() const;
    float radius() const;
    Color color() const;
    void step(double dT, const std::vector<Planet>& planets);

private:
    const float m_radius{};
    const float m_mass{};
    Vector3 m_acceleration{};
    Vector3 m_position{};
    Color m_color{};
};

void draw2d(const Planet&);
Color generateRandomColor();
