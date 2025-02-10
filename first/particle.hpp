#pragma once

#include <vector>
#include "raylib.h"

class Particle {
public:
    Particle(float x, float y, float radius)
        : position {x, y}
        , old_position {position}
        , acceleration {0.0f, 0.0f}
        , radius(radius) {
        const unsigned char R = GetRandomValue(0, 255);
        const unsigned char G = GetRandomValue(0, 255);
        const unsigned char B = GetRandomValue(0, 255);
        color = Color{R,G,B,255};
        }

    void draw() const;
    void udpatePosition(float dt);
    void accelerate(const Vector2& acc);
    float getX() const {return position.x;}
    float getY() const {return position.y;}
    float getRadius() const {return radius;}
    void setX(float x) {position.x = x;}
    void setY(float y) {position.y = y;}

    float getDistance(const Particle& particle) const;
private:
    Vector2 position;
    Vector2 old_position;
    Vector2 acceleration;
    float radius;
    Color color;
};