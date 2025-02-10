#include "simulation.hpp"
#include "particle.hpp"
#include <iostream>
#include <raymath.h>
#include <cmath>

void Simulation::update(float dt) {
    //solveCollisions();
    const int sub_step = 4;
    const float sub_dt = dt / static_cast<float>(sub_step);
    for (int i=0; i<sub_step; i++){
        updatePositions(sub_dt);
        applyConstraints();
    }
}

void Simulation::updatePositions(float dt) {
    for (Particle& particle: particles) {
        particle.udpatePosition(dt);
    }
}

void Simulation::addParticle(int x, int y, int radius) {
    // for now mass = area
    particles.push_back(Particle(x, y, radius, 2*M_PI*radius));
}

void Simulation::applyConstraints() {
    for (Particle& particle: particles) {
        // bottom
        float radius = particle.getRadius();
        if (particle.getY() + radius > height) {
            particle.setY(height - radius);
            particle.invertDampVelocityY();
        }
        // left side
        if (particle.getX() - radius < 0) {
            particle.setX(radius);
            particle.invertDampVelocityX();
        }
        // right side
        if (particle.getX() + radius > width) {
            particle.setX(width-radius);
            particle.invertDampVelocityX();
        }
    }

}

//if (position_new.x - radius < 0) {  
//    position_new.x = radius;  // Keep inside bounds
//    velocity_new.x *= -damping;  // Invert and dampen velocity
//}

void Simulation::solveCollisions() {

}

void Simulation::draw() {
    for (const Particle& particle: particles) {
        particle.draw();
    }
}