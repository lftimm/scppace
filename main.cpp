#include <vector>
#include <cmath>
#include <raylib.h>
#include <raymath.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "rlgl.h"

#include "Planet.h"
#include "Scenes.h"
#include "Consts.h"

void handleInput(Camera2D& camera);
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

                Vector2 topLeft{Vector2{-50000,-50000}};
                Vector2 bottomRight{Vector2{50000,50000}};

                for (int x = topLeft.x; x <= bottomRight.x; x += 100/camera.zoom)
                    DrawLine(x, topLeft.y, x, bottomRight.y, DARKGRAY);

                for (int y = topLeft.y; y <= bottomRight.y; y += 100/camera.zoom)
                    DrawLine(topLeft.x, y, bottomRight.x, y, DARKGRAY);

                for(Planet& p : planets)
                {
                    p.step(dT, planets);
                    draw2d(p);
                }

            EndMode2D();

            DrawFPS(Consts::getXAtWindowPercent(1)-80, Consts::getYAtWindowPercent(0.005));
            GuiComboBox(Rectangle{ 24, 24, 120, 30 }, "Black Hole;Three Body;Free Scene",&newScene);
        EndDrawing();
    }
    CloseWindow();
}

Camera2D createCamera() {
    Camera2D camera{};
    camera.offset = Vector2{0,0};
    camera.zoom = 1.f;

    return camera;
}

void handleInput(Camera2D& camera)
{
    float wheel = GetMouseWheelMove();
    if (wheel != 0)
    {
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
        camera.offset = GetMousePosition();
        camera.target = mouseWorldPos;
        float scale = 0.2f*wheel;
        camera.zoom = Clamp(expf(logf(camera.zoom)+scale), 0.025f, 5.0f);
    }

    float amount = Clamp(expf(1/camera.zoom),2.f, 5.f);
    if(IsKeyPressed(KEY_A) || IsKeyDown(KEY_A))
        camera.target.x -= amount;

    if(IsKeyPressed(KEY_D) || IsKeyDown(KEY_D))
        camera.target.x += amount;

    if(IsKeyPressed(KEY_W) || IsKeyDown(KEY_W))
        camera.target.y -= amount;

    if(IsKeyPressed(KEY_S) || IsKeyDown(KEY_S))
        camera.target.y += amount;
}

int main() {
    SetTargetFPS(60);
    InitWindow(Consts::width,Consts::height,Consts::title);
    main_loop();

    return 0;
}
