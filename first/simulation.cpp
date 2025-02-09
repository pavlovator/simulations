#include "simulation.hpp"
#include "particle.hpp"
#include <iostream>
#include <raymath.h>

void Simulation::update(float dt) {
    
    const int sub_step = 8;
    const float sub_dt = dt / (float)sub_step;
    for (int i=0; i<sub_step; i++){
        applyGravity();
        applyConstrainsCircle();
        solveCollisions();
        updatePositions(sub_dt);
    }
}

void Simulation::updatePositions(float dt) {
    for (Particle& particle: particles) {
        particle.udpatePosition(dt);
    }
}

void Simulation::addParticle(int x, int y, int radius) {
    int offset_x = GetRandomValue(-20, 20);
    int offset_y = GetRandomValue(-20, 20);

    if (x+offset_x > width || x+offset_x < 0 || y+offset_y > height || y+offset_y < 0){
        particles.push_back(Particle(x, y, radius));
        return;
    }
    particles.push_back(Particle(x+offset_x, y+offset_y, radius));
}

void Simulation::applyConstrainsCircle() {
    const Vector2 position {500.0f, 500.0f};
    const float radius = 400.0f;
    for (Particle& particle : particles) {
        const Vector2 to_obj {
            position.x - particle.getX(),
            position.y - particle.getY()
        };
        const float distance = Vector2Length(to_obj);
        if (distance > radius - 15.0f) {
            const Vector2 n {
                to_obj.x / distance,
                to_obj.y / distance
            };

            std::cout << "--------------" << "\n";
            std::cout << n.x << " n " << n.y << "\n";
            std::cout << particle.getX() << " " << particle.getY() << "\n";
            particle.setX(position.x - n.x * (radius - 15.0f));
            particle.setY(position.y - n.y * (radius - 15.0f));
            std::cout << distance << "\n";

            std::cout << particle.getX() << " " << particle.getY() << "\n";
            std::cout << "--------------" << "\n";


        }

    }
}

// not functional
void Simulation::applyConstrains() {
    for (Particle& particle : particles) {
        float p_radius = particle.getRadius();
        if (particle.getX() > width - p_radius) {
            particle.setX(width - p_radius);
            particle.reflectX();
        }
        if (particle.getX() < p_radius) {
            particle.setX(0);
            particle.reflectX();
        }
        if (particle.getY() > height - p_radius) {
            particle.setY(height - p_radius);
            particle.reflectY();
        }
        if (particle.getY() < p_radius) {
            particle.setY(0);
            particle.reflectY();
        }
    }
}

void Simulation::solveCollisions() {
    for (int i=0; i<particles.size(); i++) {
        Particle& p1 = particles[i]; 
        for (int j=i+1; j<particles.size(); j++) {
            Particle& p2 = particles[j];
            const float distance = p1.getDistance(p2);
            const float min_distance = p1.getRadius() + p2.getRadius();

            if (distance < min_distance) {
                float penetration = min_distance - distance;
                
                // Compute collision normal
                Vector2 collisionNormal = {
                    (p1.getX() - p2.getX()) / distance,
                    (p1.getY() - p2.getY()) / distance
                };
                
                p1.setX(p1.getX() + 0.5 * penetration * collisionNormal.x);
                p1.setY(p1.getY() + 0.5 * penetration * collisionNormal.y);
            
                p2.setX(p2.getX() - 0.5 * penetration * collisionNormal.x);
                p2.setY(p2.getY() - 0.5 * penetration * collisionNormal.y);
            }
        }
    }
}

void Simulation::draw() {
    DrawCircle(500, 500, 400, BLACK);
    for (const Particle& particle: particles) {
        particle.draw();
    }
}

void Simulation::applyGravity() {
    for (Particle& particle: particles) {
        particle.accelerate(gravity);
        //std::cout << particle.getX() << " " << particle.getY() << "\n";
    }
}