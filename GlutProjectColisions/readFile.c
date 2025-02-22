#include "main.h"

char* readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(sizeof(char) * (length + 1));

    size_t bytes = fread(buffer, 1, length, file);
    buffer[bytes] = '\0';
    fclose(file);

    char* values[5];
    for (int i = 0; i < 5; i++) {
        values[i] = (char*)malloc(sizeof(char) * 50);
        if (!values[i]) {
            perror("Failed to allocate memory for values");
            for (int j = 0; j < i; j++) {
                free(values[j]);
            }
            free(buffer);
            return NULL;
        }
        values[i][0] = '\0'; 
    }

    int pointNumber = 0;
    char* start = buffer;
    while (*start != '\0' && pointNumber < 5) {
        char* colon = strchr(start, ':');
        if (colon) {
            char* comma = strchr(colon + 1, ',');
            if (!comma) {
                comma = strchr(colon + 1, '\0');
            }
            int length = comma - (colon + 1);
            strncpy(values[pointNumber], colon + 1, length);
            values[pointNumber][length] = '\0'; 
            pointNumber++;
            start = comma + 1;
        }
        else {
            break;
        }
    }

    parameters.rc = atof(values[0]);
    parameters.width = atoi(values[1]);
    parameters.height = atoi(values[2]);
    parameters.nSpheres = atoi(values[3]);
    parameters.mode = atoi(values[4]);

    for (int i = 0; i < 5; i++) {
        free(values[i]);
    }
    free(buffer);
}
