#include "Consts.h"
#include "Planet.h"

#include <random>
#include <raylib.h>
#include <raymath.h>
#include <vector>

Planet::Planet(double x, double y, double radius, double mass) 
    : Planet(Vector3{static_cast<float>(x),static_cast<float>(y),0}, radius, mass) {

}

Planet::Planet(Vector3 pos, double radius, double mass) 
    : speed(Vector3Zero()),
      m_radius(radius),
      m_mass(mass),
      m_acceleration(Vector3Zero()),
      m_position(pos),
      m_color(generateRandomColor()) {
    
}

Vector3 Planet::position() const {
    return m_position;
}

float Planet::radius() const {
    return m_radius;
}

Color Planet::color() const {
    return m_color;
}

Vector3 Planet::gravityAt(const Planet& other) const {
    return gravityAt(other.m_position, other.m_mass);
}

Vector3 Planet::gravityAt(Vector3 pos, double mass) const {
    float forceMag(Consts::uniGConst * m_mass * mass);

    Vector3 toVec = Vector3Subtract(pos, m_position);
    float toVecLength{Vector3Length(toVec) + 100.f};

    return  Vector3Scale(toVec, forceMag / (toVecLength*toVecLength*toVecLength));
}

void Planet::step(double dT, const std::vector<Planet>& planets) 
{
    m_acceleration = Vector3Zero();

    for(const Planet& p : planets)
    {
        Vector3 gravVector{gravityAt(p)};
        m_acceleration += gravVector / m_mass;
    }

    speed += m_acceleration * dT;
    m_position += speed * dT;
}

void draw2d(const Planet& planet) {
    Vector3 pos{planet.position()};
    DrawCircle(pos.x, pos.y, planet.radius(), planet.color());
}

Color generateRandomColor() {
    static std::random_device dev;
    static std::mt19937 rng(dev());
    static std::uniform_int_distribution<std::mt19937::result_type> dist255(100,255);

    return Color{
        static_cast<unsigned char>(dist255(rng)),
        static_cast<unsigned char>(dist255(rng)),
        static_cast<unsigned char>(dist255(rng)),
        255
    };
}

