#include "raylib.h"
#include "simulation.hpp"
#include <iostream>

// inspired by 
// https://www.youtube.com/watch?v=lS_qeBy3aQI
// also includes link to the git repo

int main(void) {
    // Initialization
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 1000;
    int FPS = 60;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Verlet");
    SetTargetFPS(FPS);

    Simulation sim(SCREEN_WIDTH, SCREEN_HEIGHT);
    const int PARTICLE_RADIUS = 10;

    while (!WindowShouldClose()) {
        // Event Handling
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse_position = GetMousePosition();
            std::cout << mouse_position.x << " " << mouse_position.y << std::endl;
            sim.addParticle(mouse_position.x, mouse_position.y, PARTICLE_RADIUS);
        }

        // Update
        float dt = GetFrameTime();
        sim.update(dt);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        sim.draw();
        EndDrawing();
    }

    // De-Initialization
    CloseWindow();
    return 0;
}
