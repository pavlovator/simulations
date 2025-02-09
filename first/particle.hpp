#pragma once

#include <vector>
#include "raylib.h"

class Particle {
public:
    Particle(float x, float y, int radius)
        : position {x, y}
        , old_position {position}
        , acceleration {0.0f, 0.0f}
        , radius(radius) {}

    void draw() const;
    void udpatePosition(float dt);
    void accelerate(const Vector2& acc);
    float getX() const {return position.x;}
    float getY() const {return position.y;}
    int getRadius() const {return radius;}
    void setX(float x) {position.x = x;}
    void setY(float y) {position.y = y;}
    void reflectX() {old_position.x = position.x + (position.x - old_position.x);}
    void reflectY() {old_position.y = position.y + (position.y - old_position.y);}

    float getDistance(const Particle& particle) const;
private:
    Vector2 position;
    Vector2 old_position;
    Vector2 acceleration;
    int radius;
};