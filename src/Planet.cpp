#include "Consts.h"
#include "Planet.h"

#include <vector>
#include <random>
#include <omp.h>

#include <raylib.h>
#include <raymath.h>

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

Planet::Planet(double x, double y, double radius, double mass, Vector3 speed) 
    : Planet(Vector3{static_cast<float>(x),static_cast<float>(y),0}, radius, mass, speed) {
}

Planet::Planet(Vector3 pos, double radius, double mass, Vector3 speed) 
      : m_radius(radius),
        m_mass(mass),
        m_acceleration(Vector3Zero()),
        m_position(pos),
        m_speed(speed),
        m_color(generateRandomColor()) {

}

Vector3 Planet::position() const {
    return m_position;
}

float Planet::mass() const {
    return m_mass;
}

float Planet::radius() const {
    return m_radius;
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

Vector3 Planet::calc_gravity(const std::vector<Planet>& planets) 
{
    Vector3 gravVector{Vector3Zero()};
    for(const Planet& p : planets)
        gravVector = Vector3Add(gravVector,gravityAt(p));

    return gravVector;
}

void Planet::update_position(const float dT, const Vector3& force)
{
    m_acceleration = Vector3Zero();

    m_acceleration += force / m_mass;

    m_speed += m_acceleration * dT;
    m_position += m_speed * dT;
}

void draw2d(const Planet& planet) {
    Vector3 pos{planet.position()};
    DrawCircle(pos.x, pos.y, planet.radius(), planet.m_color);
}


