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
    void addParticle(int x, int y, int radius);
    void applyConstraints();
    void solveCollisions();
    void draw();
private:
    int width;
    int height;
    Vector2 gravity;
    std::vector<Particle> particles;
};