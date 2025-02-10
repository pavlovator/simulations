#pragma once
#include "raylib.h"
#include "particle.hpp"


class Simulation {
public:
    Simulation(int width, int height)
        : width {width}
        , height{height}
        , gravity {0, 1000.0f} {}

    void update(float dt);
    void updatePositions(float dt);
    void applyGravity();
    void addParticle(int x, int y, int radius);
    void applyConstrains();
    void applyConstrainsCircle();
    void solveCollisions();
    void draw();
    
private:
    int width;
    int height;
    Vector2 gravity;
    std::vector<Particle> particles;
};