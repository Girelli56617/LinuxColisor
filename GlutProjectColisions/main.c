#include "main.h"

Camera camera;
Parameters parameters;
Sphere *sphere;

int main(int argc, char* argv[]) {

	srand((int)time(NULL));

	Jogo jogo;
	int done = 0;

	readFile("parameterFile.txt");
	glutInit(&argc, argv);

	sphere = (Sphere*)malloc(sizeof(Sphere) * parameters.nSpheres);

	glewInit();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glEnable(GL_DEPTH_TEST);

	glutInitWindowSize(parameters.width, parameters.height);

	glutInitWindowPosition(0, 0);
	
	jogo.windowId = glutCreateWindow("teste");

	glutFullScreen();

	//inicializa a c�mera
	cameraInit();

	for (int i = 0; i < parameters.nSpheres; i++) { 
		sphereInit(&sphere[i]);
	}

	//Fun��o para redimensionar o tamanho da tela
	glutReshapeFunc(resize);

	// passa uma refer�ncia de process Ascii Input para glutKeyboardFunc
	glutKeyboardFunc(processAsciiInput);

	// passa uma refer�ncia de processMouseInput para glutKeyboardFunc
	glutPassiveMotionFunc(processMouseInput);

	// passa uma refer�ncia de renderScene para glutDisplayFunc
	glutDisplayFunc(renderScene);

	glutIdleFunc(requestRenderUpdate);

	glutMainLoop();

	glutDestroyWindow(jogo.windowId);

	free(sphere);

	return 0;
}