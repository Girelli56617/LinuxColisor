#include "main.h"

void drawText(float x, float y, const char* text) {
	glRasterPos2f(x, y);
	for (int i = 0; text[i] != '\0'; i++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
	}
}


void cameraInit() {
	camera.positionX = 0.0f;
	camera.positionY = 1.0f;
	camera.positionZ = 3.0f;

	camera.directionX = 0.0f;
	camera.directionY = 1.0f;
	camera.directionZ = -1.0f;

	camera.angleX = 0.0f;
	camera.angleY = 0.0f;
	camera.pitch = -89.0f;
	camera.yaw = 0.0f;

	camera.time = 0;
	camera.deltaTime = 0;

	glutSetCursor(GLUT_CURSOR_NONE);
}

void sphereInit(Sphere *sphereN) {

	sphere->spherePosition[0] = 0.0;
    sphere->spherePosition[1] = 0.0;
    sphere->spherePosition[2] = 0.0;

	sphere->speed[0] = 0.0;
	sphere->speed[1] = 0.0;
	sphere->speed[2] = 0.0;

	sphere->previousTime = 0.0f;
    
	sphereN->sectorCount = 36;
	sphereN->stackCount = 36;
	sphereN->radius = 1.0f;
	sphereN->spherePosition[0] = (float)rand() / RAND_MAX * 2.0f - 14.0f;
	sphereN->spherePosition[1] = (float)rand() / RAND_MAX * 2.0f - 14.0f;
	sphereN->spherePosition[2] = (float)rand() / RAND_MAX * 2.0f - 14.0f;
	sphereN->init = 0;

	sphereN->speed[0] = (float)rand() / RAND_MAX * 2.0f - 10.0f;
	sphereN->speed[1] = (float)rand() / RAND_MAX * 2.0f - 10.0f;
	sphereN->speed[2] = (float)rand() / RAND_MAX * 2.0f - 10.0f;

	sphereN->mass = 1.0f;

	sphereN->status = 0;

	if (!sphereN->status) {
		glEnable(GL_TEXTURE_2D);

		char* textures[10] = {
			"zelensky2.jpg",
			"prigozhin2.jpeg",
			"prigozhin.jpeg",
			"images.jpeg",
			"socialCredits.png",
			"socialCredit.jpeg",
			"maxresdefault.jpg",
			"hqdefault.jpg",
			"Winnie.jpeg",
			"PRC.png",
		};

		int randomNumber = rand() % 10;

		if (randomNumber != 4 && randomNumber != 9) {
			loadTexture(textures[randomNumber], sphereN);
		}
		else {
			loadTexture(textures[randomNumber], sphereN);
		}
	}
	generateRandomDirection(sphereN);
}

void renderScene() {

	int currentTime = glutGet(GLUT_ELAPSED_TIME);

	double deltaTime = (double)(currentTime - sphere->previousTime) / 1000.0;
	
	sphere->previousTime = currentTime;
	glClearColor(0.33f, 0.91f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(
		camera.positionX, camera.positionY, camera.positionZ,
		camera.directionX + camera.positionX,
		camera.directionY + camera.positionY,
		camera.directionZ + camera.positionZ,
		0.0f, 1.0f, 0.0f
	);

	glColor3f(0.8f, 0.8f, 0.8f);

	glBegin(GL_QUADS);

	glVertex3f(-150.0f, 0.0f, -150.0f); 
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(150.0f, 0.0f, -150.0f);  
	glColor3f(0.32f, 0.67f, 1.0f);
	glVertex3f(150.0f, 0.0f, 150.0f);   
	glColor3f(0.74f, 0.86f, 0.45);
	glVertex3f(-150.0f, 0.0f, 150.0f);  

	glEnd();

	drawBox(30.0f, 30.0f, 30.0f);

	for (int i = 0; i < parameters.nSpheres; i++) {
		updateSpherePosition(&sphere[i], deltaTime);
	}

	for (int i = 0; i < parameters.nSpheres; i++) {
		for (int j = i + 1; j < parameters.nSpheres; j++) {
			handleCollision(&sphere[i], &sphere[j], parameters.rc, deltaTime);
		}
	}

	for (int i = 0; i < parameters.nSpheres; i++) {
		glPushMatrix();
		if (parameters.mode) {
			drawColoredSphere(0.5f, 36, 36, &sphere[i]);
		}
		else {
			drawColoredSphereTextured(0.5f, 36, 36, &sphere[i]);
		}
		glPopMatrix();
	}

	glutSwapBuffers();
}


//ajusta a proje��o dos objetos quando a janela tem seu tamanho modificado

void resize(int weight, int height) {

	//impede uma divis�o por zero

	if(height == 0){
		height = 1;
	}

	float ratio = (float)weight / height;

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	//O que ser� renderizado na tela
	glViewport(0, 0, weight, height);

	//define o "furstrum"
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);

}

//redesenha a tela
void requestRenderUpdate() {
	glutPostRedisplay();
}