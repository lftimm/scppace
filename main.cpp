#include <cmath>
#include <execution>
#include <algorithm>
#include <raylib.h>
#include <raymath.h>
#include <vector>

#include "Planet.h"
#include "PlanetGenerator.h"
#include "Consts.h"

void handleInput(Camera2D& camera);

template<typename D, typename P>
constexpr void main_loop(D&& drawing, P&& physics) noexcept {

    double initialTime{GetTime()};

    Camera2D camera{};
    float x = Consts::getXAtWindowPercent(0.5);
    float y = Consts::getYAtWindowPercent(0.5);
    camera.target = {x,y};
    camera.offset = { 
            x,y
    };

    camera.rotation = 0.f;
    camera.zoom = 1.f;

    while(!WindowShouldClose())
    {
        const double currentTime{GetTime()};
        const double dT{currentTime-initialTime};

        initialTime = currentTime;
        if(dT <= 0)
            continue;

        physics(dT); 

        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(BLACK);

        handleInput(camera);

        drawing();

        EndMode2D();
        EndDrawing();
    }
    CloseWindow();
}

void handleInput(Camera2D& camera)
{
    float scale = 0.2f*GetMouseWheelMove();
    camera.zoom = expf(logf(camera.zoom)+scale);

    float amount = Clamp(expf(1/camera.zoom),2.f, 5.f);
    if(IsKeyPressed(KEY_A) || IsKeyDown(KEY_A))
        camera.offset.x += amount;

    if(IsKeyPressed(KEY_D) || IsKeyDown(KEY_D))
        camera.offset.x -= amount;

    if(IsKeyPressed(KEY_W) || IsKeyDown(KEY_W))
        camera.offset.y += amount;

    if(IsKeyPressed(KEY_S) || IsKeyDown(KEY_S))
        camera.offset.y -= amount;
}

int main() {
    SetTargetFPS(60);
    InitWindow(Consts::width,Consts::height,Consts::title);

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

    auto physics = [&](const double dT){
        std::for_each(std::execution::par, planets.begin(), planets.end(),
        [&](Planet& s) {
            s.step(dT, planets);
        });
    };

    auto drawing = [&](){
        for(const Planet& s :  planets)
            draw2d(s);
    };

    main_loop(drawing, physics);

    return 0;
}
