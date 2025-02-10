#pragma once

#include <vector>
#include "raylib.h"


class Particle {
public:
    Particle(float x, float y, float radius, float mass)
        : position {x, y}
        , velocity {0.0f, 0.0f}
        , acceleration {0.0f, 0.0f}
        , radius(radius)
        , mass(mass) {
        const unsigned char R = GetRandomValue(20, 200);
        const unsigned char G = GetRandomValue(20, 200);
        const unsigned char B = GetRandomValue(20, 200);
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
    void invertDampVelocityX();
    void invertDampVelocityY();

private:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    const Vector2 GRAVITY {0.0f, 9.81};
    float radius;
    float mass;
    const float damping = 0.5f;
    Color color;
};