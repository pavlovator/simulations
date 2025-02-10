#include "particle.hpp"
#include <raylib.h>
#include <raymath.h>
#include <iostream>

void Particle::draw() const {
    DrawCircle(position.x, position.y, radius, color);
}

// Velovity verlot
void Particle::udpatePosition(float dt) {
    // # Math: x(t+\Delta t) = x(t) + v(t)\Delta t + \frac{1}{2}a(t)\Delta t^{2}
    Vector2 position_new {
        position.x + velocity.x * dt + (acceleration.x * dt * dt)/2.0f,
        position.y + velocity.y * dt + (acceleration.y * dt * dt)/2.0f
    };
    std::cout << position.x + velocity.x * dt + (acceleration.x * dt * dt)/2.0f << std::endl;
    std::cout << position.x << " " << velocity.x << " " << dt << " " << acceleration.x << std::endl;


    // # Math: a(t+\Delta t) = f(x(t+\Delta t))
    Vector2 acceleration_new = GRAVITY * mass;

    // # Math: v(t+\Delta t) = v(t) + \frac{a(t)+a(t+\Delta t)}{2} \Delta t
    Vector2 velocity_new {
        velocity.x + ((acceleration.x + acceleration_new.x)/2.0f) * dt,
        velocity.y + ((acceleration.y + acceleration_new.y)/2.0f) * dt
    };
    position = position_new;
    acceleration = acceleration_new;
    velocity = velocity_new;
}

void Particle::invertDampVelocityX() {
    velocity.x *= (-damping);
}

void Particle::invertDampVelocityY() {
    velocity.y *= (-damping);
}

float Particle::getDistance(const Particle& particle) const {
    return Vector2Distance(position, {particle.getX(), particle.getY()});
}