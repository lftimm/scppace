#include <iostream>
#include <vector>
#include <cmath>

#include <raylib.h>
#include <raymath.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "Planet.h"
#include "Scenes.h"
#include "Consts.h"

void handleInput(Camera2D& camera);
void drawUI(int* scene);

Camera2D createCamera();

void main_loop() noexcept {
    double initialTime{GetTime()};
    Camera2D camera{createCamera()};

    int oldScene{Scenes::BlackHole};
    int newScene{};

    std::vector<Planet> planets{Scenes::next(Scenes::BlackHole)};
    while(!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(BLACK);
       
            drawUI(&newScene);
            if(newScene != oldScene)
            {
                planets = Scenes::next(static_cast<Scenes::Scene>(newScene));
                oldScene = newScene;
            }

            handleInput(camera);

            const double currentTime{GetTime()};
            const double dT{currentTime-initialTime};
            initialTime = currentTime;
            if(dT <= 0)
                continue;

            BeginMode2D(camera);
                for(Planet& p : planets)
                {
                    p.step(dT, planets);
                    draw2d(p);
                }
            EndMode2D();

        EndDrawing();
    }
    CloseWindow();
}

Camera2D createCamera() {
    Camera2D camera{};
    float x = Consts::getXAtWindowPercent(0.5);
    float y = Consts::getYAtWindowPercent(0.5);
    camera.target = {x,y};
    camera.offset = { 
            x,y
    };
    camera.rotation = 0.f;
    camera.zoom = 1.f;

    return camera;
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

void drawUI(int* scene)
{
    GuiComboBox(Rectangle{ 24, 24, 120, 30 }, "Black Hole;Three Body;Free Scene", scene);
}

int main() {
    SetTargetFPS(60);
    InitWindow(Consts::width,Consts::height,Consts::title);
    main_loop();

    return 0;
}
