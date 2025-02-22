#include "main.h"

void normalize(float* vector) {
    float magnitude = sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
    vector[0] /= magnitude;
    vector[1] /= magnitude;
    vector[2] /= magnitude;
}

void generateRandomDirection(Sphere * sphereN) {
    sphereN->direction[0] = (float)rand() / RAND_MAX * 2.0f - 1.0f;
    sphereN->direction[1] = (float)rand() / RAND_MAX * 2.0f - 1.0f;
    sphereN->direction[2] = (float)rand() / RAND_MAX * 2.0f - 1.0f;
    normalize(sphereN->direction);
}

double clamp(double value, double min, double max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void updateSpherePosition(Sphere* sphereN, double deltaTime) {
    sphereN->spherePosition[0] += sphereN->speed[0] * deltaTime;
    sphereN->spherePosition[1] += sphereN->speed[1] * deltaTime;
    sphereN->spherePosition[2] += sphereN->speed[2] * deltaTime;

    if (sphereN->spherePosition[0] + sphereN->radius > 15.0f || sphereN->spherePosition[0] - sphereN->radius < -15.0f) {
        sphereN->speed[0] *= -1;
        sphereN->spherePosition[0] = clamp(sphereN->spherePosition[0], -15.0f + sphereN->radius, 15.0f - sphereN->radius);
    }

    if (sphereN->spherePosition[1] + sphereN->radius > 15.0f || sphereN->spherePosition[1] - sphereN->radius < -15.0f) {
        sphereN->speed[1] *= -1;
        sphereN->spherePosition[1] = clamp(sphereN->spherePosition[1], -15.0f + sphereN->radius, 15.0f - sphereN->radius);
    }

    if (sphereN->spherePosition[2] + sphereN->radius > 15.0f || sphereN->spherePosition[2] - sphereN->radius < -15.0f) {
        sphereN->speed[2] *= -1;
        sphereN->spherePosition[2] = clamp(sphereN->spherePosition[2], -15.0f + sphereN->radius, 15.0f - sphereN->radius);
    }

    double systemTotalEnergy = 0;
    for (int i = 0; i < parameters.nSpheres; i++) { 
        double sqrSpeed = dotProduct(sphere[i].speed, sphere[i].speed);
        systemTotalEnergy += sqrt(sqrSpeed) * sqrt(sqrSpeed) / 2;
    }

    glColor3f(0.0f, 0.0f, 0.0f); 
    char textToDisplay[100];
    sprintf(textToDisplay, "%s", "Energia Total (Sistema): ");
    drawText(20.0f, 5.0f, textToDisplay); 

    glColor3f(1.0f, 1.0f, 0.0f);
    char textToDisplay2[50];
    sprintf(textToDisplay2, "%lf", systemTotalEnergy);
    drawText(20.0f, 3.0f, textToDisplay2);
}

void drawColoredSphereTextured(float radius, int sectorCount, int stackCount, Sphere * sphereN) {
    float x, y, z;
    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;

    glBindTexture(GL_TEXTURE_2D, sphereN->textureId); 

    glBegin(GL_QUADS);

    for (int i = 0; i < stackCount; i++) {
        float stackAngle1 = M_PI / 2 - i * stackStep;
        float stackAngle2 = M_PI / 2 - (i + 1) * stackStep;
        float xy1 = radius * cos(stackAngle1);
        float xy2 = radius * cos(stackAngle2);
        float z1 = radius * sin(stackAngle1);
        float z2 = radius * sin(stackAngle2);

        for (int j = 0; j < sectorCount; ++j) {
            float sectorAngle1 = j * sectorStep;
            float sectorAngle2 = (j + 1) * sectorStep;

            float u1 = (float)j / sectorCount;
            float u2 = (float)(j + 1) / sectorCount;
            float v1 = 1.0f - (float)i / stackCount; 
            float v2 = 1.0f - (float)(i + 1) / stackCount;

            x = xy1 * cos(sectorAngle1);
            y = xy1 * sin(sectorAngle1);
            glTexCoord2f(u1, v1); 
            glVertex3f(x + sphereN->spherePosition[0], y + sphereN->spherePosition[1], z1 + sphereN->spherePosition[2]);

            x = xy2 * cos(sectorAngle1);
            y = xy2 * sin(sectorAngle1);
            glTexCoord2f(u1, v2);
            glVertex3f(x + sphereN->spherePosition[0], y + sphereN->spherePosition[1], z2 + sphereN->spherePosition[2]);

            x = xy2 * cos(sectorAngle2);
            y = xy2 * sin(sectorAngle2);
            glTexCoord2f(u2, v2); 
            glVertex3f(x + sphereN->spherePosition[0], y + sphereN->spherePosition[1], z2 + sphereN->spherePosition[2]);

            x = xy1 * cos(sectorAngle2);
            y = xy1 * sin(sectorAngle2);
            glTexCoord2f(u2, v1);
            glVertex3f(x + sphereN->spherePosition[0], y + sphereN->spherePosition[1], z1 + sphereN->spherePosition[2]);
        }
    }

    glEnd();
}

void drawColoredSphere(float radius, int sectorCount, int stackCount, Sphere* sphereN) {
    float x, y, z;
    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;

    glBegin(GL_QUADS);

    for (int i = 0; i < stackCount; i++) {
        float stackAngle1 = M_PI / 2 - i * stackStep;
        float stackAngle2 = M_PI / 2 - (i + 1) * stackStep;
        float xy1 = radius * cos(stackAngle1);
        float xy2 = radius * cos(stackAngle2);
        float z1 = radius * sin(stackAngle1);
        float z2 = radius * sin(stackAngle2);

        for (int j = 0; j < sectorCount; ++j) {
            float sectorAngle1 = j * sectorStep;
            float sectorAngle2 = (j + 1) * sectorStep;

            x = xy1 * cos(sectorAngle1);
            y = xy1 * sin(sectorAngle1);
            glColor3f(fabs(x), fabs(y), fabs(z1)); 
            glVertex3f(x + sphereN->spherePosition[0], y + sphereN->spherePosition[1], z1 + sphereN->spherePosition[2]);

            x = xy2 * cos(sectorAngle1);
            y = xy2 * sin(sectorAngle1);
            glColor3f(fabs(x), fabs(y), fabs(z2));
            glVertex3f(x + sphereN->spherePosition[0], y + sphereN->spherePosition[1], z2 + sphereN->spherePosition[2]);

            x = xy2 * cos(sectorAngle2);
            y = xy2 * sin(sectorAngle2);
            glColor3f(fabs(x), fabs(y), fabs(z2));
            glVertex3f(x + sphereN->spherePosition[0], y + sphereN->spherePosition[1], z2 + sphereN->spherePosition[2]);

            x = xy1 * cos(sectorAngle2);
            y = xy1 * sin(sectorAngle2);
            glColor3f(fabs(x), fabs(y), fabs(z1));
            glVertex3f(x + sphereN->spherePosition[0], y + sphereN->spherePosition[1], z1 + sphereN->spherePosition[2]);
        }
    }

    glEnd();
}

void drawBox(float width, float height, float depth) {
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 0.0f);

    glScalef(width, height, depth);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(1.0f, 1.0f, 1.0f); 

    glutSolidCube(1.0f); 

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glPopMatrix();
}

void loadTexture(const char* filename, Sphere* sphereN) {
    int width, height, channels;
    stbi_uc* imageData = stbi_load(filename, &width, &height, &channels, 0);

    if (!imageData) {
        printf("Failed to load texture: %s\n", filename);
        exit(1);
    }

    glGenTextures(1, &sphereN->textureId);
    glBindTexture(GL_TEXTURE_2D, sphereN->textureId);

    if (channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    }
    else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(imageData);
}
