#pragma once
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include <time.h>
#include "../libraries/stb/stb_image.h"

#define M_PI 3.14159265358979323846

typedef struct {
	float directionX, directionY, directionZ;
	float positionX, positionY, positionZ;
	float angleX, angleY, pitch, yaw;
	int time, deltaTime;
	float xMotion, yMotion;
}Camera;

typedef struct {
	int sectorCount, stackCount;
	double radius, spherePosition[3], direction[3], speed[3], init;
	float mass;
	unsigned int textureId;
	short status;
	int previousTime;
}Sphere;

typedef struct{
	int windowId;
}Jogo;

typedef struct {
	double rc;
	int width;
	int height;
	int nSpheres;
	short mode;
}Parameters;


extern Camera camera;
extern Parameters parameters;
extern Sphere *sphere;

void renderScene();
void processAsciiInput(unsigned char characterKey);
void resize(int weight, int height);
void cameraInit();
void processMouseInput(int x, int y);
void requestRenderUpdate();
void crossProduct(float v1[3], float v2[3], float v3[3]);
void drawColoredSphere(float radius, int sectorCount, int stackCount, Sphere *sphere);
void updateSpherePosition(Sphere* sphere, double deltaTime);
void normalize(float* vector);
void generateRandomDirection(Sphere* sphere);
void drawColoredSphereTextured(float radius, int sectorCount, int stackCount, Sphere* sphere);
void sphereInit(Sphere* sphere);
void drawBox(float width, float height, float depth);
void handleCollision(Sphere* sphere1, Sphere* sphere2, double restitution, double deltaTime);
void loadTexture(const char* filename, Sphere* sphereN);
void drawText(float x, float y, const char* text);
char* readFile(const char* filename);
double dotProduct(double v1[3], double v2[3]);