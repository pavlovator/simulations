#include "simulation.hpp"
#include "particle.hpp"
#include <iostream>
#include <raymath.h>

void Simulation::update(float dt) {
    
    const int sub_step = 4;
    const float sub_dt = dt / (float)sub_step;
    for (int i=0; i<sub_step; i++){
        applyGravity();
        solveCollisions();
        applyConstrainsCircle();
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
        if (distance > radius - particle.getRadius()) {
            const Vector2 n {
                to_obj.x / distance,
                to_obj.y / distance
            };
            particle.setX(position.x - n.x * (radius - particle.getRadius()));
            particle.setY(position.y - n.y * (radius - particle.getRadius()));
        }

    }
}

void Simulation::solveCollisions() {
    const float response_coef = 0.75f;
    for (int i=0; i<particles.size(); i++) {
        Particle& p1 = particles[i]; 
        for (int j=i+1; j<particles.size(); j++) {
            Particle& p2 = particles[j];
            // const float distance = p1.getDistance(p2);
            // const float min_distance = p1.getRadius() + p2.getRadius();

            // if (distance < min_distance) {
            //     float penetration = min_distance - distance;
                
            //     // Compute collision normal
            //     Vector2 collisionNormal = {
            //         (p1.getX() - p2.getX()) / distance,
            //         (p1.getY() - p2.getY()) / distance
            //     };
                
            //     p1.setX(p1.getX() + 0.5 * penetration * collisionNormal.x);
            //     p1.setY(p1.getY() + 0.5 * penetration * collisionNormal.y);
            
            //     p2.setX(p2.getX() - 0.5 * penetration * collisionNormal.x);
            //     p2.setY(p2.getY() - 0.5 * penetration * collisionNormal.y);
            // }
            const Vector2 v {
                p1.getX() - p2.getX(),
                p1.getY() - p2.getY()
            };
            const float dist2 = v.x * v.x + v.y * v.y;
            const float min_dist = p1.getRadius() + p2.getRadius();
            if (dist2 < min_dist * min_dist) {
                const float dist = sqrt(dist2);
                const Vector2 n {v.x / dist, v.y / dist};
                const float mass_ratio_1 = p1.getRadius() / (p1.getRadius() + p2.getRadius());
                const float mass_ratio_2 = p2.getRadius() / (p1.getRadius() + p2.getRadius());
                const float delta = 0.5 * response_coef * (dist - min_dist);
                p1.setX(p1.getX() - n.x * (mass_ratio_2 * delta));
                p1.setY(p1.getY() - n.y * (mass_ratio_2 * delta));
            
                p2.setX(p2.getX() + n.x * (mass_ratio_1 * delta));
                p2.setY(p2.getY() + n.y * (mass_ratio_1 * delta));
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