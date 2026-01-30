#pragma once

#include <raylib.h>
#include <vector>
#include <raymath.h>

class Planet
{
private:
    const float m_radius{};
    const float m_mass{};
    Vector3 m_acceleration{};
    Vector3 m_position{};
    Vector3 m_speed{};
    Color m_color{};

public:
    Planet(double, double, double, double, Vector3);
    Planet(Vector3, double, double, Vector3);

    Vector3 gravityAt(const Planet&) const;
    Vector3 gravityAt(const Vector3, double) const;

    float mass() const;
    Vector3 position() const;
    float radius() const;
    Color color() const;

    Vector3 calc_gravity(const std::vector<Planet>&);
    void update_position(const float, const Vector3&);

    friend void draw2d(const Planet&);
};

