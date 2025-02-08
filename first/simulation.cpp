#include "simulation.hpp"
#include "particle.hpp"

void Simulation::update(float dt) {
    applyGravity();
    updatePositions(dt);
    applyConstrains();
    solveCollisions();
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

void Simulation::applyConstrains() {
    for (Particle& particle : particles) {
        if (particle.getX() > width) {
            particle.setX(width);
        }
        if (particle.getX() < 0) {
            particle.setX(0);
        }
        if (particle.getY() > height) {
            particle.setY(height);
        }
        if (particle.getY() < 0) {
            particle.setY(0);
        }
    }
}

void Simulation::solveCollisions() {
    for (int i=0; i<particles.size(); i++) {
        Particle& p1 = particles[i]; 
        for (int j=i+1; j<particles.size(); j++) {
            Particle& p2 = particles[j];
            float distance = p1.getDistance(p2);
            float min_distance = p1.getRadius() + p2.getRadius();
            if (distance < min_distance) {
                float penetration = min_distance - distance;
                
                // Compute collision normal
                Vector2 collisionNormal = {
                    (p1.getX() - p2.getX()) / distance,
                    (p1.getY() - p2.getY()) / distance
                };

                // Compute mass ratio based on radii (for simplicity, using radii as a stand-in for mass)
                float total_radius = p1.getRadius() + p2.getRadius();
                float mass_ratio1 = p1.getRadius() / total_radius;
                float mass_ratio2 = p2.getRadius() / total_radius;
            
                // Move the particles apart, weighted by their radii (masses)
                p1.setX(p1.getX() + mass_ratio2 * penetration * collisionNormal.x);
                p1.setY(p1.getY() + mass_ratio2 * penetration * collisionNormal.y);
            
                p2.setX(p2.getX() - mass_ratio1 * penetration * collisionNormal.x);
                p2.setY(p2.getY() - mass_ratio1 * penetration * collisionNormal.y);
            
            }
        }
    }
}

void Simulation::draw() {
    for (const Particle& particle: particles) {
        particle.draw();
    }
}

void Simulation::applyGravity() {
    for (Particle& particle: particles) {
        particle.accelerate(gravity);
    }
}