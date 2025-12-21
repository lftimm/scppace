#include "headers/Circle.h"
#include "headers/Cts.h"

#include <raylib.h>
#include <vector>

template<typename D, typename P>
void main_loop(D&& drawing, P&& physics) {
    double initialTime{GetTime()};

    while(!WindowShouldClose())
    {
        const double currentTime{GetTime()};
        const double dT{currentTime-initialTime};

        initialTime = currentTime;
        if(dT <= 0)
            continue;

        physics(dT); 

        BeginDrawing();
            ClearBackground(BLACK);
            drawing();
        EndDrawing();
    }
    CloseWindow();
}

int main() {
    InitWindow(Cts::width,Cts::height,Cts::title.c_str());
    SetTargetFPS(60);

    Circle c{ 
        Cts::getXAtWindowPercent(0.5),
        Cts::getYAtWindowPercent(0.5),
        0,
        100
    };

    std::vector<SimObject*> objects{&c};    

    auto physics = [&](const double dT){
        for(const auto& s : objects)
            s->step(dT);
    };

    auto drawing = [&](){
        for(const auto& s :  objects)
            s->draw();
    };

    main_loop(drawing, physics);

    return 0;
}
