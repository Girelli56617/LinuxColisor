#include "main.h"

#define EPSILON 1e-6f

void handleCollision(Sphere* sphere1, Sphere* sphere2, double restitution, double deltaTime) {
    double normal[3];
    double distanceSquared = 0.0f;

    for (int i = 0; i < 3; i++) {
        normal[i] = sphere1->spherePosition[i] - sphere2->spherePosition[i];
        distanceSquared += normal[i] * normal[i];
    }

    double radiusSum = sphere1->radius + sphere2->radius;
    if (distanceSquared >= radiusSum * radiusSum || distanceSquared < EPSILON) {
        return;
    }

    double distance = sqrt(distanceSquared);

    for (int i = 0; i < 3; i++) {
        normal[i] /= distance;
    }

    double relativeVelocity[3];
    for (int i = 0; i < 3; i++) {
        relativeVelocity[i] = sphere1->speed[i] - sphere2->speed[i];
    }

    double dotProduct = 0.0f;
    for (int i = 0; i < 3; i++) {
        dotProduct += relativeVelocity[i] * normal[i];
    }

    if (dotProduct >= 0.0f) {
        return;
    }

    double impulse = (1.0f + restitution) * dotProduct;

    double totalMass = sphere1->mass + sphere2->mass;

    for (int i = 0; i < 3; i++) {
        sphere1->speed[i] -= impulse * normal[i] * (sphere2->mass / totalMass);
        sphere2->speed[i] += impulse * normal[i] * (sphere1->mass / totalMass); 
    }

    double penetrationDepth = radiusSum - distance;

    double correctionFactor1 = sphere2->mass / totalMass;
    double correctionFactor2 = sphere1->mass / totalMass;

    for (int i = 0; i < 3; i++) {
        sphere1->spherePosition[i] += penetrationDepth * normal[i] * correctionFactor1;
        sphere2->spherePosition[i] -= penetrationDepth * normal[i] * correctionFactor2;
    }

    for (int i = 0; i < 3; i++) {
        sphere1->spherePosition[i] += sphere1->speed[i] * deltaTime;
        sphere2->spherePosition[i] += sphere2->speed[i] * deltaTime; 
    }
}