#include "particle.hpp"
#include <raylib.h>
#include <raymath.h>
#include <iostream>

void Particle::draw() const {
    DrawCircle(position.x, position.y, radius, DARKBLUE);
    std::cout << position.x << " " << position.y << std::endl;
}

void Particle::udpatePosition(float dt) {
    old_position = position;
    Vector2 velocity {position.x - old_position.x, position.y - old_position.y};
    
    //position = position + velocity + acceleration * dt * dt
    position.x = position.x + velocity.x + acceleration.x * dt * dt;
    position.y = position.y + velocity.y + acceleration.y * dt * dt;
}

void Particle::accelerate(Vector2 acc) {
    acceleration.x += acc.x;
    acceleration.y += acc.y; 
}

float Particle::getDistance(const Particle& particle) const {
    return Vector2Distance(position, {particle.getX(), particle.getY()});
}
