#include "main.h"

void processAsciiInput(unsigned char characterKey) {
	if (characterKey == 27) {
		exit(0);
	}
	if (characterKey == 97) {
		float vector1[3], vector2[3] = { 0.0f, 1.0f, 0.0f }, resultantVector[3];
		vector1[0] = camera.directionX;
		vector1[1] = 0.0f;
		vector1[2] = camera.directionZ;
		crossProduct(vector1, vector2, resultantVector);

		//normalizacao
		normalize(resultantVector);

		camera.positionX -= resultantVector[0] * 2.5f;
		camera.positionY -= resultantVector[1] * 2.5f;
		camera.positionZ -= resultantVector[2] * 2.5f;
	}
	if (characterKey == 100) {
		float vector1[3], vector2[3] = {0.0f, 1.0f, 0.0f}, resultantVector[3];
		vector1[0] = camera.directionX;
		vector1[1] = 0.0f;
		vector1[2] = camera.directionZ;
		crossProduct(vector1, vector2, resultantVector);

		//normalizacao
		normalize(resultantVector);

		camera.positionX += resultantVector[0] * 2.5f;
		camera.positionY += resultantVector[1] * 2.5f;
		camera.positionZ += resultantVector[2] * 2.5f;
	}
	if (characterKey == 115) {
		camera.positionX -= camera.directionX * 2.5f;
		camera.positionY -= camera.directionY * 2.5f;
		camera.positionZ -= camera.directionZ * 2.5f;
	}
	if (characterKey == 119) {
		camera.positionX += camera.directionX * 2.5f;
		camera.positionY += camera.directionY * 2.5f;
		camera.positionZ += camera.directionZ * 2.5f;
	}
}

void processMouseInput(int x, int y) {
	
	double deltaX = x - camera.angleX;
	double deltaY = y - camera.angleY;

	if (x <= 0 || x >= parameters.width - 1 || y <= 0 || y >= parameters.height - 1) {
		glutWarpPointer(parameters.width/2, parameters.height/2);
		x = parameters.width / 2;
		y = parameters.height / 2;
	}

	//sensibilidade
	deltaX *= 0.05f;
	deltaY *= 0.05f; 

	camera.pitch += deltaY * M_PI / 180.0;
	camera.yaw += deltaX * M_PI / 180.0;

	if (camera.pitch > 89.0f) {
		camera.pitch = 89.0f;
	}
	if (camera.pitch < -89.0f) {
		camera.pitch = -89.0f;
	}

	camera.directionX = cos(camera.pitch) * cos(camera.yaw);
	camera.directionY = sin(camera.pitch);
	camera.directionZ = sin(camera.yaw) * cos(camera.pitch);

	camera.angleX = x;
	camera.angleY = y;
}

void crossProduct(float v1[3], float v2[3], float v3[3]) {
	v3[0] = v1[1] * v2[2] - v1[2] * v2[1];
	v3[1] = v1[2] * v2[0] - v1[0] * v2[2];
	v3[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

double dotProduct(double v1[3], double v2[3]) {
	double result;
	result = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
	return result;
}